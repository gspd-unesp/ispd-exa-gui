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
    // PC item
    QImage pcImg(":icons/pc.png");
    QImage npcImg = pcImg.scaled(QSize(70, 70), Qt::KeepAspectRatio);
    this->headp = new QImage(npcImg);

    // Cluster item
    QImage clusterImg(":icons/cluster.png");
    QImage nclusterImg = clusterImg.scaled(QSize(70, 70), Qt::KeepAspectRatio);
    this->headc = new QImage(nclusterImg);
    this->current_item = nullptr;

    // Button PC Icon
    this->buttonPCIcon = new QImage(":/icons/pc.png");
    //this->ui->buttonA->setCursor(Qt::PointingHandCursor);
    this->ui->buttonPC->setIcon(QIcon(QPixmap::fromImage(*buttonPCIcon)));
    // this->ui->buttonA->setStyleSheet("QPushButton {background-color: #2bc48a; border-radius: 3px;}""QPushButton:hover { border-color: #4A69BD; border-width: 1px; border-style:inset; background-color: #29bc78}");
    this->ui->buttonPC->setFixedSize(50, 40);
    this->ui->buttonPC->setIconSize(QSize(35, 35));

    // Button Cluster Icon
    this->buttonClusterIcon = new QImage(":/icons/cluster.png");
    //this->ui->buttonA->setCursor(Qt::PointingHandCursor);
    this->ui->buttonCluster->setIcon(QIcon(QPixmap::fromImage(*buttonClusterIcon)));
    // this->ui->buttonA->setStyleSheet("QPushButton {background-color: #2bc48a; border-radius: 3px;}""QPushButton:hover { border-color: #4A69BD; border-width: 1px; border-style:inset; background-color: #29bc78}");
    this->ui->buttonCluster->setFixedSize(50, 40);
    this->ui->buttonCluster->setIconSize(QSize(35, 35));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonB_clicked()
{
    this->userWindow = new UserWindow();
    this->userWindow->show();
}

void MainWindow::on_buttonC_clicked()
{
    this->workloadsWindow = new Workloads();
    this->workloadsWindow->show();
}

void MainWindow::on_buttonPC_clicked()
{
    this->current_item = new GridItem(QPixmap::fromImage(*headp), ui);
    this->current_item->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(this->current_item);
    this->ui->grid->show();
}

void MainWindow::on_buttonCluster_clicked()
{
    this->current_item = new GridItem(QPixmap::fromImage(*headc), ui);
    this->current_item->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(this->current_item);
    this->ui->grid->show();
}



