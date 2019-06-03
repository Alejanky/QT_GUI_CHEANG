#include "mainwindow.h"
#include <QApplication>

#include<QtCore>
#include<thread.h>

int main(int argc, char *argv[])
{
    QApplication* a = new QApplication(argc, argv);
    MainWindow* w = new MainWindow();
    w->show();
    return a->exec();
}
