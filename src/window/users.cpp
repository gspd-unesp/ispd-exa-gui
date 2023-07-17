#include "window/users.h"
#include <QPushButton>
#include <QSettings>
#include <ui_userwindow.h>
#include <QSettings>
#include "drawingtable/drawingtable.h"


UserWindow::UserWindow(QWidget *parent, DrawingTable *drawingTable, const QList<QString> &list1Data, const QList<double> &list2Data)
    : QMainWindow(parent), ui(new Ui::UserWindow)
{
    ui->setupUi(this);

    this->drawingTable = drawingTable;
    // Add a close icon and a add icon
    this->fecharImg = new QImage(":/icons/x_button.png");
    this->addIcon   = new QImage(":/icons/add_icon.png");
    // Remove button Stylesheet
    this->ui->pushButton->setCursor(Qt::PointingHandCursor);
    this->ui->pushButton->setIcon(QIcon(QPixmap::fromImage(*fecharImg)));
    this->ui->pushButton->setStyleSheet(
        "QPushButton {background-color: #f53b57; border-radius: 3px;}"
        "QPushButton:hover { border-color: #4A69BD; border-width: 1px; "
        "border-style:inset; background-color: #e90c2d;}");
    this->ui->pushButton->setFixedSize(50, 22);
    this->ui->pushButton->setIconSize(QSize(14, 14));
    // Add Button Stylesheet
    this->ui->addButton->setCursor(Qt::PointingHandCursor);
    this->ui->addButton->setIcon(QIcon(QPixmap::fromImage(*addIcon)));
    this->ui->addButton->setStyleSheet(
        "QPushButton {background-color: #2bc48a; border-radius: 3px;}"
        "QPushButton:hover { border-color: #4A69BD; border-width: 1px; "
        "border-style:inset; background-color: #29bc78}");
    this->ui->addButton->setFixedSize(50, 22);
    this->ui->addButton->setIconSize(QSize(12, 12));

    // addOnList1("user1");
    // addOnList2(100);

    ui->listWidget->addItems(list1Data);
    for (const double value : list2Data)
    {
        ui->listWidget_2->addItem(QString::number(value));
    }
}

UserWindow::~UserWindow()
{
    delete ui;
}

void UserWindow::addOnList1(const QString &valor)
{

    ui->listWidget->addItem(valor);
}

void UserWindow::addOnList2(double valor)
{
    QString strValor = QString::number(valor); // Converter o double para QString
    ui->listWidget_2->addItem(strValor);
}

void UserWindow::on_addButton_clicked()
{
    this->adduser = new addUser();
    this->adduser->show();
}


void UserWindow::on_pushButton_clicked()
{
    if(mnSelected != -1)
    {

        QListWidgetItem *it2 = ui->listWidget_2->takeItem(mnSelected);
        QListWidgetItem *it = ui->listWidget->takeItem(mnSelected);

        delete it;
        delete it2;


        ui->listWidget_2->setCurrentRow(-1);
        ui->listWidget->setCurrentRow(-1);
    }
}


void UserWindow::on_listWidget_currentRowChanged(int currentRow)
{
    mnSelected = currentRow;
}

void UserWindow::setDrawingTable(DrawingTable* drawingTable)
{
    this->drawingTable = drawingTable;
}

void UserWindow::on_listWidget_2_currentRowChanged(int currentRow)
{
    mnSelected = currentRow;
}


void UserWindow::on_okButton_clicked()
{
    if (drawingTable)
    {
        qDebug() << "Entrou aqui";
        QList<QString> list1Data;
        QList<double> list2Data;

               // Copy the items from listWidget and listWidget_2 to the new QLists
        for (int i = 0; i < ui->listWidget->count(); ++i)
        {
            list1Data.append(ui->listWidget->item(i)->text());
        }

        for (int i = 0; i < ui->listWidget_2->count(); ++i)
        {
            list2Data.append(ui->listWidget_2->item(i)->text().toDouble());
        }

               // Call the function in DrawingTable to receive the data
        drawingTable->receiveUserWindowData(list1Data, list2Data);
    }
    close();
}

void UserWindow::clearListWidgets()
{
    ui->listWidget->clear();
    ui->listWidget_2->clear();
}
