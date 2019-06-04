/////////// Includes//////////////////////
///

    #include "mainwindow.h"
    #include "ui_mainwindow.h"

///

///////////Class Methods//////////////////
///

    MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow){
        ui->setupUi(this);
    }

    MainWindow::~MainWindow(){
        delete ui;
    }

///

///////////Private Methods//////////////////
///



///

///////////Public Methods//////////////////
///

    void MainWindow::setThread(Thread* ser){
            this->server1 = ser;
    }

///


///////////Clicked Events//////////////////
///

    void MainWindow::on_pB_Log_clicked(){
        Roomf_Form *al;
        al = new Roomf_Form();
        connect(al,&Roomf_Form::new_room,this,&MainWindow::new_room);
        ui->tabWidget->setTabsClosable(true);
        ui->tabWidget->addTab(al,"cuarto1");
       // ui->tabWidget->setCurrentIndex(2);
       // ui->tabWidget->removeTab(0);
        //ui->tabWidget->removeTab(0);
    }

    void MainWindow::on_pB_Test2_clicked(){
       // server1->StartThread();
        server1->start();
    }

    void MainWindow::on_pB_Test_clicked(){

    }

    void MainWindow::on_pB_Conn_clicked(){

    }

    void MainWindow::on_pB_state_clicked(){
        int x =1;
        this->server1->c_State(x);
    }

    void MainWindow::on_pB_CreateLS_clicked(){
        if(this->server1!=nullptr){
            ///
            ///
            /// o marco una senal para marcar error
            /// o borro  la implementacion anterior
            /// y desconecto cliente y servidor
            ///  :C fuuuck
        }else{
            Thread* localServer;
            localServer=  new Thread();
            this->setThread(localServer);
        }
    }

    void MainWindow::on_pB_ALS_clicked(){
        QObject::connect(server1,&Thread::resultReady,this,&MainWindow::updateLabel);
        QObject::connect(server1,&Thread::commServer,this,&MainWindow::server_EM);

    }

    void MainWindow::on_pB_StartLS_clicked(){
        server1->StartThread(0,1);
        server1->start();

    }

    void MainWindow::on_pB_EndLS_clicked(){
        server1->cut();
    }

    void MainWindow::on_pB_DeleteLS_clicked(){
        server1->terminate();
        QObject::disconnect(server1,&Thread::resultReady,this,&MainWindow::updateLabel);
        QObject::disconnect(server1,&Thread::commServer,this,&MainWindow::server_EM);
        server1= nullptr;
    }

    void MainWindow::on_pB_CCS_clicked(){
        if(this->serverClient!=nullptr){
            /// o marco una senal para marcar error
            /// o borro  la implementacion anterior
            /// y desconecto cliente y servidor
            ///  :C fuuuck
        }else{
            Thread* Cservice;
            Cservice = new Thread();
            this->serverClient = Cservice;
        }
        //Connect signal and
    }

    void MainWindow::on_pB_ACS_clicked(){
        QObject::connect(serverClient,&Thread::resultReady,this,&MainWindow::updateLabel2);
        QObject::connect(serverClient,&Thread::commClient,this,&MainWindow::client_EM);
    }

    void MainWindow::on_pB_ConnCS_clicked(){
        QString a = ui->le_Server->text();
        serverClient->StartThread(0,0);
        serverClient->set_serverIP(a);
        serverClient->clientConnect();
        serverClient->start();
    }

    void MainWindow::on_pB_SmCS_clicked(){

    }

    void MainWindow::on_pB_Cstate_clicked(){
        QString a= ui->le_Message->text();
        serverClient->c_State(a.toInt());
    }

    void MainWindow::on_pB_EndCS_clicked(){
        serverClient->cut();
    }

    void MainWindow::on_pB_DeleteCS_clicked(){
        serverClient->terminate();
        QObject::disconnect(serverClient,&Thread::resultReady,this,&MainWindow::updateLabel2);
        QObject::disconnect(serverClient,&Thread::commClient,this,&MainWindow::client_EM);
        serverClient= nullptr;
    }

///

///////////Public Slots//////////////////
///

    void MainWindow::updateLabel( QString str ){
        ui->l_Recived->setText(str);
        ui->l_Recived->adjustSize();
    }


    void MainWindow::updateLabel2( QString str ){
        ui->lBcStatus->setText(str);
        ui->lBcStatus->adjustSize();
    }

    void  MainWindow::new_room(){
        Roomf_Form *al;
        al = new Roomf_Form();
       connect(al,&Roomf_Form::new_room,this,&MainWindow::new_room);
         ui->tabWidget->setTabsClosable(true);
        ui->tabWidget->addTab(al,"cuarto2");
    }

    void MainWindow::server_EM(QString value){
        ui->l_Recived->setText(value);
        ui->l_Recived->adjustSize();
        ui->tE_textLS->append(value);
    }

    void MainWindow::client_EM(QString value){
        ui->lBcStatus->setText(value);
        ui->lBcStatus->adjustSize();
        //ui->tE_test->append(value);
        ui->tE_textCS->append(value);

    }

///
