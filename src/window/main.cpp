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
#include <QSettings>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}, ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);
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
    this->scene->pickOp = SCHEMA;
}

void MainWindow::on_bLink_clicked()
{
    this->scene->pickOp = LINK;
}

