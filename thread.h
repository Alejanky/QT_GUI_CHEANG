    #ifndef THREAD_H
    #define THREAD_H
    #undef UNICODE
    #define WIN32_LEAN_AND_MEAN
    #include <Windows.h>
    #include <WinSock2.h>
    #include <WS2tcpip.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string>
    #include <cstring>
    #include<QDebug>
    // Need to link with Ws2_32.lib
    #pragma comment (lib, "Ws2_32.lib")
    // #pragma comment (lib, "Mswsock.lib")
    #define DEFAULT_BUFLEN 1024
    #define DEFAULT_PORT "7789"
    #include <QtCore>
    #include <QString>

    class Thread : public QThread{
    Q_OBJECT
    public:
        void StartThread( int x , int y);
        void c_State(int a);
        void set_Message(QString x);
        void set_serverIP(QString z);
        void client(int x);
        void server();
        void cut();
        void terminate();
        void clientConnect();

        signals:
            void resultReady( QString str);
            void commClient(QString str);
            void commServer (QString str);

    private:
        void  run()  ;
        void sendy(QString str,char* buffer);
        void clientEx();
        void serverEx();



    private:
        WSADATA wsaData;
        int iResult;
        int state = 0; // state = 0  DO NOTHING
        int tp=0; //  type of thread client or server
        SOCKET ListenSocket = INVALID_SOCKET;
        SOCKET ClientSocket = INVALID_SOCKET;
        struct addrinfo *result = NULL,*ptr = NULL;
        struct addrinfo hints;
        int iSendResult;
        char recvbuf[DEFAULT_BUFLEN];
        int recvbuflen = DEFAULT_BUFLEN;
        std::string message;
        QString qs;
    };

    #endif // THREAD_H
