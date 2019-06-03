    #ifndef CONTROLLER_H
    #define CONTROLLER_H

    #include <QObject>
    #include <QThread>
    #include <worker.h>

    class Controller : public QObject
    {
        Q_OBJECT
         QThread* workerThread;
    public:
        Controller() {
            Worker *worker = new Worker;
            worker->moveToThread(workerThread);
            connect(workerThread, &QThread::finished, worker, &QObject::deleteLater);
            connect(this, &Controller::operate, worker, &Worker::doWork);
           // connect(worker, &Worker::resultReady, this, &Controller::handleResults);
            workerThread->start();
        }
        ~Controller() {
            workerThread->quit();
            workerThread->wait();
        }
    public slots:
        void handleResults(QString str);

    signals:
        void operate(QString str);

    };

    #endif // CONTROLLER_H
