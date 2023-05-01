#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "griditem.h"
#include "gridscene.h"
#include "userwindow.h"
#include "workloads.h"

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
    QImage pcImg(":icons/pc.png");
    QImage npcImg = pcImg.scaled(QSize(70, 70), Qt::KeepAspectRatio);
    this->head = new QImage(npcImg);
    this->current_item = nullptr;

}

MainWindow::~MainWindow()
{
    delete ui;
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
    this->current_item = new GridItem(QPixmap::fromImage(*head), ui);
    this->current_item->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(this->current_item);
    this->ui->grid->show();
}



