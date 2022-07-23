#include "WorkerThread.h"

#include <QTimer>
#include <QRandomGenerator>

WorkerThread::WorkerThread(QObject *parent)
    : QThread(parent)
{
}

void WorkerThread::run()
{
    m_pStatus = Status::Runned;

    GeneratNewPointsSlot();

    QElapsedTimer timer;
    timer.start();

    //Ожидание окончания работы
    while (!QThread::currentThread()->isInterruptionRequested())
    {
        //Ожидание генерации значений
        if (m_pStatus == Status::Runned && static_cast<size_t>(timer.elapsed()) > m_renderingPeriod)
        {
            GeneratNewPointsSlot();

            timer.start();
        }
    }
}

void WorkerThread::GeneratNewPointsSlot()
{
    QVector<QPointF> points;

    //QRandomGenerator::global()->generateDouble() генерирует число в диапазоне [0, 1)
    for (size_t i=0; i<m_pointsCount; i++)
    {
        points.push_back({
            QRandomGenerator::global()->generateDouble(),
            QRandomGenerator::global()->generateDouble()});
    }

    emit GeneratedNewPointsSignal(points);
}

void WorkerThread::Continue()
{
    m_pStatus = Status::Runned;
}

void WorkerThread::Pause()
{
    m_pStatus = Status::Paused;
}
