#include "roomf_form.h"
#include "ui_roomf_form.h"

Roomf_Form::Roomf_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Roomf_Form)
{
    ui->setupUi(this);
}

Roomf_Form::~Roomf_Form()
{
    delete ui;
}

void Roomf_Form::on_pB_NCuarto_clicked()
{
    emit new_room();
}

void Roomf_Form::on_pB_Mensaje_clicked()
{
    if(this->ui->lE_Cuarto->text()==""){
        QString x = "Todavia no te has Suscrito a un room";
            this->ui->lE_Mensaje->setText(x);
    }else{
        QString a =this->ui->lE_Mensaje->text();
        this->serverClient->set_Room(this->ui->lE_Cuarto->text());
        this->serverClient->set_Message(a);
        this->serverClient->c_State(1);
    }
}

void Roomf_Form::on_pB_TCuarto_clicked()
{
    if(this->ui->lE_Cuarto->text()=="" || this->ui->lE_Cuarto->text() == " "){
        QString x = "El Cuerto no puede estar vacio o con empezando con espacio";
            this->ui->lE_Mensaje->setText(x);
    }else{
        this->Room=  this->ui->lE_Cuarto->text();
        this->serverClient->set_Room(this->ui->lE_Cuarto->text());
        this->serverClient->c_State(2);
    }
}

void Roomf_Form::on_pB_CM_clicked()
{
    //pB_CM
    if(this->Room== ""){
    }else{
        nMessages = 10;
        this->serverClient->set_Room(this->ui->lE_Cuarto->text());
        this->nMess =  QString::number(nMessages); ;
        this->serverClient->MessageN = this->nMess;
        this->serverClient->c_State(3);
    }
}
