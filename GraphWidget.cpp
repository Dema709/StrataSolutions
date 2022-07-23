#include "GraphWidget.h"

GraphWidget::GraphWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout* pMainLayout = new QVBoxLayout();
    setLayout(pMainLayout);

    fillMainLayout(pMainLayout);

    qRegisterMetaType<QVector<QPointF>>();
}

GraphWidget::~GraphWidget()
{
    stopThread();
}

void GraphWidget::StartSlot()
{
    if (!pWorkerThread)
    {
        //Запуск нового потока
        pWorkerThread = std::make_shared<WorkerThread>(this);
        connect(pWorkerThread.get(), &WorkerThread::GeneratedNewPointsSignal, this, &GraphWidget::DrawNewPointsSlot);

        pWorkerThread->start();
    }
    else
    {
        //Возобновление работы потока
        pWorkerThread->Continue();
    }
}

void GraphWidget::PauseSlot()
{
    if (pWorkerThread)
        pWorkerThread->Pause();
}

void GraphWidget::StopSlot()
{
    //Остановка потока
    stopThread();

    //Очистка графика
    if (m_pCustomPlot)
    {
        m_pCustomPlot->clearGraphs();
        m_pCustomPlot->replot();
    }
}

void GraphWidget::DrawNewPointsSlot(QVector<QPointF> points)
{
    if (!m_pCustomPlot || points.size() == 0)
        return;

    //Преобразование данных в подходящий формат
    QVector<double> x(points.size());
    QVector<double> y(points.size());
    for (auto& point : points)
    {
        x.push_back(point.x());
        y.push_back(point.y());
    }

    //Очистка графика
    m_pCustomPlot->clearGraphs();

    //Добавление новых значений
    auto* pGraph = m_pCustomPlot->addGraph();
    pGraph->setData(x, y);

    //Масштабирование графика по данным и настройки внешнего вида
    pGraph->rescaleAxes();
    pGraph->setLineStyle(QCPGraph::LineStyle::lsNone);
    pGraph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
    m_pCustomPlot->replot();
}

void GraphWidget::fillMainLayout(QVBoxLayout* pMainLayout)
{
    //График
    m_pCustomPlot = new QCustomPlot(this);
    pMainLayout->addWidget(m_pCustomPlot);
    m_pCustomPlot->setMinimumSize(200, 200);

    //Кнопки
    QHBoxLayout* pButtonsLayout = new QHBoxLayout();
    pMainLayout->addLayout(pButtonsLayout);
    {
        QPushButton* pStartPushButton = new QPushButton("Старт", this);
        pButtonsLayout->addWidget(pStartPushButton);
        connect(pStartPushButton, &QPushButton::clicked, this, &GraphWidget::StartSlot);
    }
    {
        QPushButton* pPausePushButton = new QPushButton("Пауза", this);
        pButtonsLayout->addWidget(pPausePushButton);
        connect(pPausePushButton, &QPushButton::clicked, this, &GraphWidget::PauseSlot);
    }
    {
        QPushButton* pStopPushButton = new QPushButton("Стоп", this);
        pButtonsLayout->addWidget(pStopPushButton);
        connect(pStopPushButton, &QPushButton::clicked, this, &GraphWidget::StopSlot);
    }
}

void GraphWidget::stopThread()
{
    if (pWorkerThread)
    {
        pWorkerThread->requestInterruption();
        pWorkerThread->wait();
        pWorkerThread.reset();
    }
}
