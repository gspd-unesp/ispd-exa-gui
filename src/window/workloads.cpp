#include "window/workloads.h"
#include <ui_workloads.h>

WorkloadsWindow::WorkloadsWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Workloads)
{

    ui->setupUi(this);
}

WorkloadsWindow::~WorkloadsWindow()
{
    delete ui;
}

void WorkloadsWindow::on_pushButton_clicked()
{
    QTextStream message(stdout);
    message << "Program will be closed" << Qt::endl;

    QApplication::quit();
}
