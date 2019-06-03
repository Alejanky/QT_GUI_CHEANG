#ifndef TASK_H
#define TASK_H


#pragma comment (lib, "Ws2_32.lib")
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#include <QRunnable>
#include <QObject>
 #include <QString>

class Task : public QObject, public QRunnable
{
    Q_OBJECT
public:
    Task(QObject* parentObject = 0) : QObject(parentObject) {
        WSAStartup(MAKEWORD(2,0), &WSAData);
            server = socket(AF_INET, SOCK_STREAM, 0);
            serverAddr.sin_addr.s_addr = INADDR_ANY;
            serverAddr.sin_family = AF_INET;
            serverAddr.sin_port = htons(5555);
    }

    void run() override;

signals:
    void finished(QString);

private:
       WSADATA WSAData;
       SOCKET server, client;
       SOCKADDR_IN serverAddr, clientAddr;


};


#endif // TASK_H
