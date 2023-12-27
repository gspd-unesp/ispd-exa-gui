#include "window/adduser.h"
#include <qboxlayout.h>
#include <QFormLayout>
#include <qpushbutton.h>
#include <qt5/QtWidgets/qlineedit.h>
#include <vector>

AddUserWindow::AddUserWindow(std::vector<Context::User> *users, QWidget *parent) :
      QDialog(parent), users{users}
{
    this->setMaximumWidth(300);
    auto editFrame = new QFrame();
    auto editLayout = new QFormLayout(editFrame);
    editLayout->addRow("Name:", this->nameEdit);
    editLayout->addRow("Consumption Limit:", this->consumptionEdit);

    auto buttonsFrame = new QFrame();
    auto buttonsLayout = new QHBoxLayout(buttonsFrame);
    auto okButton = new QPushButton("Ok");
    auto cancelButton = new QPushButton("Cancel");
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(okButton);
    buttonsLayout->addWidget(cancelButton);

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(editFrame);
    mainLayout->addWidget(buttonsFrame);

    connect(okButton, &QPushButton::pressed, this, &AddUserWindow::addUserAction);
    connect(cancelButton, &QPushButton::pressed, this, &AddUserWindow::cancelButtonAction);
}

void AddUserWindow::addUserAction()
{
    double usageCorrected = this->consumptionEdit->text().toDouble() / 100;

    this->users->push_back(Context::User{.name = this->nameEdit->text().toStdString(), .allowedUsage = usageCorrected});

    addAnUser();
    this->close();
}


void AddUserWindow::cancelButtonAction()
{
    close();
}
