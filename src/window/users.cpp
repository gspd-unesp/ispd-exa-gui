#include "window/users.h"
#include "window/adduser.h"
#include <QGraphicsItem>
#include <QPushButton>
#include <QSettings>
#include <qboxlayout.h>
#include <qt5/QtWidgets/qpushbutton.h>
#include <qtablewidget.h>
#include <ui_userwindow.h>

#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QMessageBox>

UserWindow::UserWindow(Context::MainContext *context, QWidget *parent)
    : QWidget(parent), context{context}
{
    // Configure main layout of the window
    auto mainLayout = new QVBoxLayout(this);

    // Create buttons row
    auto buttonFrame  = new QFrame();
    auto buttonLayout = new QHBoxLayout(buttonFrame);

    // Add more buttons as needed
    buttonLayout->addWidget(addUserB);
    buttonLayout->addWidget(deleteUserB);

    mainLayout->addWidget(buttonFrame);

    QStringList headers;
    headers << "User"
            << "Usage Limit";

    /* this->usersTable.setRowCount(1); */
    this->usersTable.setColumnCount(2);
    this->usersTable.setHorizontalHeaderLabels(headers);
    this->usersTable.horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    mainLayout->addWidget(&this->usersTable);
    this->insertUsers();

    connect(&this->usersTable, &QTableWidget::itemChanged, this, &UserWindow::onItemChanged);
    connect(this->addUserB, &QPushButton::pressed, this, &UserWindow::addUser);
}

void UserWindow::addUser() {
    auto newAddUser = new AddUserWindow(&this->context->users);

    connect(newAddUser, &AddUserWindow::addAnUser, this, &UserWindow::insertUsers);

    newAddUser->exec();
}

void UserWindow::insertUsers()
{
    while (this->usersTable.rowCount() > 0) {
        this->usersTable.removeRow(0);
    }

    this->usersTable.setRowCount(this->context->users.size());

    int i = 0;
    for (const auto iter : this->context->users) {
        this->usersTable.setItem(
            i, 0, new QTableWidgetItem(QString(iter.name.c_str())));
        this->usersTable.setItem(
            i, 1, new QTableWidgetItem(QString::number(iter.allowedUsage * 100.0) + " %"));

        i++;
    }
}

void UserWindow::onItemChanged(QTableWidgetItem *item)
{
    static QString lastString;
    if (item->column() == 1) { // Check if the change is in the 'Age' column
        if (lastString == item->text()) {
            return;
        }

        bool ok;
        int value = item->text().split(' ')[0].toInt(&ok);

        int newValue = 0;
        if (!ok || value < 0 || value > 100) { // Constraint: Age must be between 0 and 100
            QMessageBox::warning(this, "Invalid Input", "\'Allowed Usage\' must be a integer number between 0 and 100.");
            newValue = 0;
        } else {
            newValue = value;
        }

        qDebug() << item->text();

        this->context->users[item->row()].allowedUsage = newValue / 100.0;
        QString newString = QString::number(newValue) + " %";
        lastString = newString;
        item->setText(newString); // Revert to a default value
    }
}
