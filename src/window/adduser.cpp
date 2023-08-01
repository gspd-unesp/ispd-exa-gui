#include "window/adduser.h"
#include "ui_adduser.h"
#include "window/users.h"
addUser::addUser(QWidget *parent) :
      QWidget(parent),
      ui(new Ui::addUser)
{
    ui->setupUi(this);

}

addUser::~addUser()
{
    delete ui;
}


void addUser::on_okButton_clicked()
{
    QString valor1 = ui->lineEdit->text();
    QString valor2 = ui->lineEdit_2->text();

    double valor2int = valor2.toDouble();

    UserWindow *userwindow = nullptr;
    QList<QWidget*> topLevelWidgets = QApplication::topLevelWidgets();
    for (QWidget *widget : topLevelWidgets) {
        if (widget->inherits("UserWindow")) {
            userwindow = dynamic_cast<UserWindow*>(widget);
            break;
        }
    }

    if (!userwindow) {
        userwindow = new UserWindow(this);
        userwindow->show();
    }
    userwindow->addOnList1(valor1);
    userwindow->addOnList2(valor2int);

    close();
}


void addUser::on_cancelButton_clicked()
{
    close();
}
