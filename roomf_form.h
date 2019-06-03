#ifndef ROOMF_FORM_H
#define ROOMF_FORM_H

#include <QWidget>

namespace Ui {
class Roomf_Form;
}

class Roomf_Form : public QWidget
{
    Q_OBJECT

public:
    explicit Roomf_Form(QWidget *parent = nullptr);
    ~Roomf_Form();
     signals:
    void new_room();

private slots:
    void on_pB_NCuarto_clicked();

private:
    Ui::Roomf_Form *ui;
};

#endif // ROOMF_FORM_H
