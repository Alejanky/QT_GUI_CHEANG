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
