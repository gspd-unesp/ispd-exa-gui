#include "window/main.h"
#include "window/users.h"
#include "window/workloads.h"

#include "drawingtable/scene.h"

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
    this->scene                          = new Scene();
    this->scene->machineDescriptionLabel = ui->position;
    this->ui->grid->setGScene(scene);

    // Button PC Icon
    this->bPcIcon = new QImage(":/icons/pc.png");
    this->ui->bPc->setIcon(QIcon(QPixmap::fromImage(*bPcIcon)));

    // Button Cluster Icon
    //
    this->bClusterIcon = new QImage(":/icons/cluster.png");
    this->ui->bCluster->setIcon(QIcon(QPixmap::fromImage(*bClusterIcon)));

    this->bNoneIcon = new QImage(":/icons/cursor.png");
    this->ui->bNone->setIcon(QIcon(QPixmap::fromImage(*bNoneIcon)));
    this->ui->bNone->click();

    this->ui->bNone->setIconSize(QSize(35, 35));
    this->ui->bPc->setIconSize(QSize(35, 35));
    this->ui->bCluster->setIconSize(QSize(35, 35));
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
    this->workloadsWindow = new WorkloadsWindow();
    this->workloadsWindow->show();
}

void MainWindow::on_bPc_clicked()
{
    this->scene->pickOp = PC;
}

void MainWindow::on_bNone_clicked()
{
    this->scene->pickOp = NONE;
}

void MainWindow::on_bCluster_clicked()
{
    this->scene->pickOp = CLUSTER;
}

void MainWindow::on_bLink_clicked()
{
    this->scene->pickOp = LINK;
}
