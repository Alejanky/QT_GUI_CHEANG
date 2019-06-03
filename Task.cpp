#include "Task.h"

void Task::run()
{
    QString a2 ("Listening for incoming connections...");
    emit finished( a2);
    bool a=true;/*
    while(a ){
            bind(server, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
            listen(server, 0);
        char buffer[1024];
        int clientAddrSize = sizeof(clientAddr);
        if((client = accept(server, (SOCKADDR *)&clientAddr, &clientAddrSize)) != INVALID_SOCKET)
        {
            a2 ="Client connected!";
             emit finished( a2);
            recv(client, buffer, sizeof(buffer), 0);
            QString a1 (buffer);
            a1= "Client says: "+a1;
            emit finished(a1);
            memset(buffer, 0, sizeof(buffer));
            closesocket(client);
        }
    }*/

}
