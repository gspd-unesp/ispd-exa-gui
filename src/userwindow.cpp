#include "userwindow.h"
#include "ui_userwindow.h"

UserWindow::UserWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::UserWindow)
{
    ui->setupUi(this);
    // Add a close icon and a add icon
    this->fecharImg = new QImage(":/icons/x_button.png");
    this->addIcon = new QImage(":/icons/add_icon.png");
    // Remove button Stylesheet
    this->ui->pushButton->setCursor(Qt::PointingHandCursor);
    this->ui->pushButton->setIcon(QIcon(QPixmap::fromImage(*fecharImg)));
    this->ui->pushButton->setStyleSheet("QPushButton {background-color: #f53b57; border-radius: 3px;}""QPushButton:hover { border-color: #4A69BD; border-width: 1px; border-style:inset; background-color: #e90c2d;}");
    this->ui->pushButton->setFixedSize(50, 22);
    this->ui->pushButton->setIconSize(QSize(14, 14));
    // Add Button Stylesheet
    this->ui->addButton->setCursor(Qt::PointingHandCursor);
    this->ui->addButton->setIcon(QIcon(QPixmap::fromImage(*addIcon)));
    this->ui->addButton->setStyleSheet("QPushButton {background-color: #2bc48a; border-radius: 3px;}""QPushButton:hover { border-color: #4A69BD; border-width: 1px; border-style:inset; background-color: #29bc78}");
    this->ui->addButton->setFixedSize(50, 22);
    this->ui->addButton->setIconSize(QSize(12, 12));

}

UserWindow::~UserWindow()
{
    delete ui;
}
