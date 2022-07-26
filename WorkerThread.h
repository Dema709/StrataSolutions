#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include <QObject>
#include <QPoint>
#include <QVector>
#include <atomic>

//Поток генерации значений
class WorkerThread : public QThread
{
    Q_OBJECT

public:
    enum class Status
    {
        NotStarted = 0,
        Runned,
        Paused
    };

public:
    WorkerThread(QObject* parent = nullptr);

    void run() override;

public slots:
    //Генерация значений
    void GeneratNewPointsSlot();

    void Continue();
    void Pause();

signals:
    void GeneratedNewPointsSignal(QVector<QPointF> points);

private:
    std::atomic<Status> m_pStatus = {Status::NotStarted};

    //Период геренации массива значений, мс
    size_t m_renderingPeriod = 1000;
    //Размер массива значений
    size_t m_pointsCount = 10;
};

#endif // WORKERTHREAD_H
