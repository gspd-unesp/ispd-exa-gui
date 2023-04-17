#include "mainwindow.h"
#include "qgraphicsview.h"

#include "griditem.h"
#include "ui_mainwindow.h"
#include <QBrush>
#include <QColor>
#include <QFormLayout>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLineEdit>
#include <QPen>
#include <QPixmap>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) : QMainWindow{parent}, ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);
    this->scene = new GridScene();
    this->ui->grid->setScene(scene);
    this->head = new QImage(":icons/machine.png");
}

void MainWindow::on_button_b_clicked()
{
    this->userWindow = new UserWindow();
    this->userWindow->show();
}

void MainWindow::on_button_c_clicked()
{
    this->workloadsWindow = new Workloads();
    this->workloadsWindow->show();
}

void MainWindow::on_buttonA_clicked()
{
    auto new_item = new GridItem(QPixmap::fromImage(*head));
    new_item->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(new_item);
    this->ui->grid->show();
}
