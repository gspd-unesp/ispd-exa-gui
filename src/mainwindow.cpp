#include "mainwindow.h"
#include "clustericon.h"
#include "machineicon.h"

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
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}, ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);
    this->scene = new GridScene();
    this->ui->grid->setScene(scene);
    // Button PC Icon
    this->buttonPCIcon = new QImage(":/icons/pc.png");
    // this->ui->buttonA->setCursor(Qt::PointingHandCursor);
    this->ui->buttonPC->setIcon(QIcon(QPixmap::fromImage(*buttonPCIcon)));
    // this->ui->buttonA->setStyleSheet("QPushButton {background-color: #2bc48a;
    // border-radius: 3px;}""QPushButton:hover { border-color: #4A69BD;
    // border-width: 1px; border-style:inset; background-color: #29bc78}");
    this->ui->buttonPC->setFixedSize(50, 40);
    this->ui->buttonPC->setIconSize(QSize(35, 35));

    // Button Cluster Icon
    this->buttonClusterIcon = new QImage(":/icons/cluster.png");
    // this->ui->buttonA->setCursor(Qt::PointingHandCursor);
    this->ui->buttonCluster->setIcon(
        QIcon(QPixmap::fromImage(*buttonClusterIcon)));
    // this->ui->buttonA->setStyleSheet("QPushButton {background-color: #2bc48a;
    // border-radius: 3px;}""QPushButton:hover { border-color: #4A69BD;
    // border-width: 1px; border-style:inset; background-color: #29bc78}");
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
    scene->addIcon(new MachineIcon("hello"));
    this->ui->grid->show();
}

void MainWindow::on_buttonCluster_clicked()
{
    scene->addIcon(new ClusterIcon("hello"));
    this->ui->grid->show();
}
