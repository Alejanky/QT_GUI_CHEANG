#ifndef ROOMF_FORM_H
#define ROOMF_FORM_H

#include <QWidget>
#include <thread.h>

namespace Ui {
class Roomf_Form;
}

class Roomf_Form : public QWidget
{
    Q_OBJECT

public:
    explicit Roomf_Form(QWidget *parent = nullptr);
    ~Roomf_Form();
    Thread* server1 = nullptr;//Local Server
    Thread* serverClient= nullptr;// Server for Client listening
     signals:
    void new_room();


private slots:
    void on_pB_NCuarto_clicked();


    void on_pB_Mensaje_clicked();

    void on_pB_TCuarto_clicked();

private:
    Ui::Roomf_Form *ui;
};

#endif // ROOMF_FORM_H
