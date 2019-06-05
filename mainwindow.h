    #ifndef MAINWINDOW_H
    #define MAINWINDOW_H

    #define WIN32_LEAN_AND_MEAN


    #include <Windows.h>
    #include <WinSock2.h>
    #include <WS2tcpip.h>
    #include <stdlib.h>
    #include <stdio.h>


    // Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
    #pragma comment (lib, "Ws2_32.lib")
    #pragma comment (lib, "Mswsock.lib")
    #pragma comment (lib, "AdvApi32.lib")


    #include <QMainWindow>
    #include <QPushButton>
    #include <QString>
    #include <thread.h>
    #include <roomf_form.h>

    namespace Ui {
    class MainWindow;
    }

    class MainWindow : public QMainWindow
    {
        Q_OBJECT
        public:
            explicit MainWindow(QWidget *parent = nullptr);
            ~MainWindow();
           void setThread(Thread* ser);

        private slots:
            void on_pB_Log_clicked();

            void on_pB_Test_clicked();

            void on_pB_Test2_clicked();

            void on_pB_Conn_clicked();

            void on_pB_state_clicked();

            void on_pB_CreateLS_clicked();

            void on_pB_ALS_clicked();

            void on_pB_StartLS_clicked();

            void on_pB_EndLS_clicked();

            void on_pB_DeleteLS_clicked();

            void on_pB_CCS_clicked();

            void on_pB_ACS_clicked();

            void on_pB_ConnCS_clicked();

            void on_pB_SmCS_clicked();

            void on_pB_Cstate_clicked();

            void on_pB_EndCS_clicked();

            void on_pB_DeleteCS_clicked();

    private:
            Ui::MainWindow *ui;
            ///
            Thread* server1 = nullptr;//Local Server
            Thread* serverClient= nullptr;// Server for Client listening
            int Current_ClientState;

    public slots:
        void updateLabel(QString value);
        void updateLabel2(QString value);
        void new_room();
        void server_EM(QString value);
        void client_EM(QString value);

    };

    #endif // MAINWINDOW_H
