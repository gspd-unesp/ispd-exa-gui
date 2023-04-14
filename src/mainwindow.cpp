#include "../include/mainwindow.h"
#include "qgraphicsview.h"

#include "ui_mainwindow.h"
#include <QBrush>
#include <QColor>
#include <QFormLayout>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLineEdit>
#include <QPen>
#include <QPushButton>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) : QMainWindow{parent}, ui(new Ui::MainWindow){
    ui->setupUi(this);
    this->scene = new QGraphicsScene();
    this->ui->grid->setScene(scene);
    this->ui->grid->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
    this->head =  new QImage(":icons/head.png");
}


void MainWindow::on_button_a_clicked()
{
    auto new_item = new QGraphicsPixmapItem(QPixmap::fromImage(*head));
    new_item->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(new_item);
    this->ui->grid->show();
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

