#pragma once

#include "context/user.h"
#include <QWidget>
#include <QLineEdit>
#include <qdialog.h>
#include <vector>

class AddUserWindow : public QDialog
{
    Q_OBJECT

public:
    AddUserWindow(std::vector<Context::User> *users, QWidget *parent = nullptr);
    QString name;
    double consumptionLimit;
    std::vector<Context::User> *users;
    QLineEdit *nameEdit = new QLineEdit();
    QLineEdit *consumptionEdit = new QLineEdit();


private slots:
    void addUserAction();
    void cancelButtonAction();

signals:
    void addAnUser();

private:
    QLineEdit *lineEdit1;
    QLineEdit *lineEdit2;
};
