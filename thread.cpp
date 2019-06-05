#include "thread.h"
#include <QDebug>
////////declaration
void Thread::StartThread(int state,int tap){
    switch (tap) {
        case 0:// case 0 =  client  Initialize
            this->client(state);
            this->tp = tap;
        break;
        case 1:// case 1 = server Initialize
            this->server();
            this->tp = tap;
        break;
    }
}
////// main fuction
void Thread::run(){
    QString a;
    // swith for case for running  cycle for client or server
    while(runl){
        switch (this->tp) {
            case 0:{
                    // case 0 =  client  Initialize
                    this->clientEx();
                   }
                break;
            case 1:// case 1 = server Initialize
                this->serverEx();
        }
    }
}

void Thread::client(int state){
    this->state = state;
    QString a;
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        a ="WSAStartup failed with error: ";
        char aChar = '0' + iResult;
         a = a + aChar;
         emit commClient(a);
        // send emmit for soket to change text
    }
}

void Thread::clientConnect(){
    QString a;
    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    // Resolve the server address and port
    // socket to get ip adress
    std::string current_locale_text = qs.toLocal8Bit().constData();
    const char *cstr = current_locale_text.c_str();
    iResult = getaddrinfo(cstr, DEFAULT_PORT, &hints, &result);
    if ( iResult != 0 ) {
        a="getaddrinfo failed with error: ";
        char aChar = '0' + iResult;
        a = a + aChar;
        emit commClient(a);
        WSACleanup();
    }

    // Attempt to connect to an address until one succeeds
    for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {
        // Create a SOCKET for connecting to server
        ClientSocket = socket(ptr->ai_family, ptr->ai_socktype,
        ptr->ai_protocol);
        if (ClientSocket == INVALID_SOCKET) {
            a="socket failed with error: \n" ;
            char aChar = '0' + WSAGetLastError();
            a = a + aChar;
            emit commClient(a);
            WSACleanup();
        }
        // Connect to server.
        iResult = ::connect( ClientSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ClientSocket);
            ClientSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }
    freeaddrinfo(result);
    if (ClientSocket == INVALID_SOCKET) {
        a="Unable to connect to server!";
        emit commClient(a);
        WSACleanup();
        this->terminate();
    }else{
        a="Connectes Succesfully at server";
        emit commClient(a);
    }

}

void Thread::clientEx(){
    switch (this->state) {
        case 0:// case 0 =  client listens
            this->State0();
        break;
        case 1:// case 1 = client sends message to server;
            this->State1();
        break;
        case 2: //case 2 = Subribe to a room
            this->State2();
        break;
        case 3: //case 3 = Query older messages
            this->State3();
        break;
        case 4: //case 4 = Query older messages
            this->State4();
        break;
    }
}

void Thread::server(){
    QString a;
    state= 0;
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        a="WSAStartup failed with error: \n";
        char aChar = '0' + iResult;
         a = a + aChar;
         emit resultReady(a);
    }
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;
    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if ( iResult != 0 ) {
        a="getaddrinfo failed with error: \n";
        char aChar = '0' + iResult;
         a = a + aChar;
        WSACleanup();
        emit resultReady(a);
        emit commServer(a);
    }
    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        a="socket failed with error: \n";
        char aChar = '0' + WSAGetLastError();
         a = a + aChar;
        freeaddrinfo(result);
        WSACleanup();
           emit resultReady(a);
        emit commServer(a);
    }
    // Setup the TCP listening socket
    iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        a="bind failed with error: \n";
        char aChar = '0' + WSAGetLastError();
         a = a + aChar;
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
           emit resultReady(a);
        emit commServer(a);
    }
    freeaddrinfo(result);
    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        a="listen failed with error: \n";
        char aChar = '0' + WSAGetLastError();
         a = a + aChar;
        closesocket(ListenSocket);
        WSACleanup();
        emit resultReady(a);
        emit commServer(a);
    }
    a = "started server correctly";
    emit resultReady(a);
    emit commServer(a);
}

void Thread::serverEx(){
    QString a;
    // Accept a client socket
    if(ClientSocket ==INVALID_SOCKET){
        ClientSocket = accept(ListenSocket, NULL, NULL);
        if (ClientSocket == INVALID_SOCKET) {
            a="accept failed with error: \n";
            char aChar = '0' + WSAGetLastError();
            a = a + aChar;
            closesocket(ListenSocket);
            WSACleanup();
            emit commServer(a);
        }
    }
    // No longer need server socket
    closesocket(ListenSocket);
    // Receive until the peer shuts down the connection
    do {
        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0) {
            if(state==0){
                a="Bytes received: server \n";
                a= a+ " : "+ recvbuf;
                emit commServer(a);
            }
            else{
                a="Bytes received: server \n";
                a= a+ " : "+ recvbuf +"state change :"+ state;
                emit commServer(a);
            }
            iSendResult = send( ClientSocket, recvbuf, recvbuflen, 0 );
            if (iSendResult == SOCKET_ERROR) {
                a="send failed with error: %d\n";
                char aChar = '0' + WSAGetLastError();
                a = a + aChar;
                closesocket(ClientSocket);
                WSACleanup();
                emit commServer(a);
            }
            a="Bytes sent: server\n";
            a= a +recvbuf;
            emit commServer(a);
        }
        else if (iResult == 0){
            a="Connection closing...\n";
            emit commServer(a);
        }
        else{
            a="recv failed with error: \n";
            char aChar = '0' + WSAGetLastError();
            a = a + aChar;
            closesocket(ClientSocket);
            WSACleanup();
            emit commServer(a);
        }
    } while (iResult > 0);
}

void Thread::cut(){
    QString a;
    // depending on the TP  we neeed to close the loop and conection a clean up the socket
    if(this->tp ==0){
        // shutdown the connection since no more data will be sent
        closesocket(ClientSocket);
        WSACleanup();
        a= "client cut";
        emit commClient(a);
        this->terminate();
    }else{
        // shutdown the connection since we're done
        iResult = shutdown(ClientSocket, SD_SEND);
        if (iResult == SOCKET_ERROR) {
            a="shutdown failed with error: \n";
            char aChar = '0' + WSAGetLastError();
            a = a + aChar;
            closesocket(ClientSocket);
            WSACleanup();
            emit commServer(a);
        }
       // cleanup
       closesocket(ClientSocket);
       WSACleanup();
       a= "server cut";
       emit commServer(a);
        this->terminate();
    }

}

void Thread::terminate(){
    // <-- wits till the thread has exited
    this->deleteLater();
    this->runl = false;
}


void Thread::State0(){
     // Receive until the peer closes the connection
    /// aqui tengo que utilzar el select y si no sale el timout entonces  buelbo ha preguntar
    QString a;
    fd_set ReadFDs;
    FD_ZERO(&ReadFDs);
    FD_SET(ClientSocket, &ReadFDs);
            struct timeval *tv = new timeval();
            tv->tv_sec = 0;
            tv->tv_usec = 250000;
    if(::select(0,&ReadFDs ,NULL, NULL,tv) != 0){
        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        if ( iResult > 0 ){
            a="Bytes received cliente:\n";
            a+= recvbuf;
            emit commClient(a);
        }
        else if ( iResult == 0 ){
            a="Connection closed\n";
           emit commClient(a);
        }
        else{
            a="recv failed with error: %d\n";
                char aChar = '0' + WSAGetLastError();
            a=a+ aChar;
            emit commClient(a);
        }
    }else{
        a = "pasaron 200 millisegundos y voy a repetirlo escuchandoooo.....";
        emit commClient(a);
    }
}

void Thread::State1(){
    // state to send message
    QString a;
     a = "p|";
     a =  a + this->Room;
    std::string xs  = a.toLocal8Bit().constData();
    xs = xs + "|";
    xs = xs + this->message;
    xs = xs + "|";
    xs = xs + this->Poster.toLocal8Bit().constData();
    const char *cstr = xs.c_str();
    int i = (int)xs.length();
        iResult = send( ClientSocket, cstr,i, 0 );
        a="Bytes Sent:\n";
        a = a+ cstr;
        emit commClient(a);
    if (iResult == SOCKET_ERROR) {
        a="send failed with error: ";
        char aChar = '0' + WSAGetLastError();
        a = a + aChar;
        emit commClient(a);
        closesocket(ClientSocket);
        WSACleanup();
    }
     this->state = 0;
}

void Thread::State2(){
    QString a;
     a = "s|";
     a =  a + this->Room;
    std::string xs  = a.toLocal8Bit().constData();
    const char *cstr = xs.c_str();
    int i = (int)xs.length();
        iResult = send( ClientSocket, cstr,i, 0 );
        a="Bytes Sent:\n";
        a = a+ cstr;
        emit commClient(a);
    if (iResult == SOCKET_ERROR) {
        a="send failed with error: ";
        char aChar = '0' + WSAGetLastError();
        a = a + aChar;
        emit commClient(a);
        closesocket(ClientSocket);
        WSACleanup();
    }
     this->state = 0;
}

void Thread::State3(){
    QString a;
     a = "m|";
     a =  a + this->Room;
    std::string xs  = a.toLocal8Bit().constData();
    xs = xs + "|";
    xs = xs + this->message;   ///pos
    xs = xs + "|";
     xs = xs + this->message;   ///nmemb

    const char *cstr = xs.c_str();
    int i = (int)xs.length();
        iResult = send( ClientSocket, cstr,i, 0 );
        a="Bytes Sent:\n";
        a = a+ cstr;
        emit commClient(a);
    if (iResult == SOCKET_ERROR) {
        a="send failed with error: ";
        char aChar = '0' + WSAGetLastError();
        a = a + aChar;
        emit commClient(a);
        closesocket(ClientSocket);
        WSACleanup();
    }
     this->state = 0;
}

void Thread::State4(){
    QString a;
     a = "n|";
     a =  a + this->Poster;
    std::string xs  = a.toLocal8Bit().constData();
    const char *cstr = xs.c_str();
    int i = (int)xs.length();
        iResult = send( ClientSocket, cstr,i, 0 );
        a="Bytes Sent:\n";
        a = a+ cstr;
        emit commClient(a);
    if (iResult == SOCKET_ERROR) {
        a="send failed with error: ";
        char aChar = '0' + WSAGetLastError();
        a = a + aChar;
        emit commClient(a);
        closesocket(ClientSocket);
        WSACleanup();
    }
     this->state = 0;

}

///////// Set and setting Variables /////////////////
void Thread::c_State(int a){
    this->state = a ;
}

void Thread::set_Message(QString x){
    this->message = x.toLocal8Bit().constData();
}

void Thread::set_serverIP(QString z){
    this->qs = z;
}

void Thread::set_Room(QString str){
    this->Room = str;
}

void Thread::set_Poster(QString str){
    this->Poster = str;
}

void Thread::set_Sub(QString str){
    this->Sub = str;
}
