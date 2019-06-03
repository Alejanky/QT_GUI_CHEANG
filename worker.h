#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QString>

class Worker : public QObject
{
    Q_OBJECT

 public slots:
     void doWork() {
         QString result;
         /* ... here is the expensive or blocking operation ... */
         emit resultReady(result);
     }

 signals:
     void resultReady( QString result);
};

#endif // WORKER_H
