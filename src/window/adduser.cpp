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

    double valor2int = valor2.toDouble(); // Conversão de QString para double

    // Verifica se a janela UserWindow já está aberta
    UserWindow *userwindow = nullptr;
    QList<QWidget*> topLevelWidgets = QApplication::topLevelWidgets();//lista que irá armazenar ponteiros para os widgets de nível superior na aplicação
    for (QWidget *widget : topLevelWidgets) {
        if (widget->inherits("UserWindow")) {
            userwindow = dynamic_cast<UserWindow*>(widget);//Caso o widget seja uma instância da classe UserWindow ou de uma classe derivada, converter o ponteiro widget para um ponteiro do tipo UserWindow*
            break;
        }
    }



    if (!userwindow) {
        userwindow = new UserWindow(this);
        userwindow->show();
    }

           // Adiciona os valores na lista existente
    userwindow->addOnList1(valor1);
    userwindow->addOnList2(valor2int);

    close();
}


void addUser::on_cancelButton_clicked()
{
    close();
}
