#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <memory>
#include "QCustomPlot/qcustomplot.h"
#include "WorkerThread.h"

//Виджет для управления потоком генерации и отображения получаемых значений
class GraphWidget : public QWidget
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = nullptr);
    ~GraphWidget();

public slots:
    //Запуск/восстановление работы потока
    void StartSlot();
    //Постановка потока на паузу
    void PauseSlot();
    //Остановка потока и очистка графика
    void StopSlot();

    //Отрисовка массива значений
    void DrawNewPointsSlot(QVector<QPointF> points);

private:
    void fillMainLayout(QVBoxLayout* pMainLayout);
    //Остановка потока
    void stopThread();

private:
    QCustomPlot* m_pCustomPlot = nullptr;
    std::shared_ptr<WorkerThread> pWorkerThread;
};
#endif // GRAPHWIDGET_H
