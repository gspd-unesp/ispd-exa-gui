#include "workloads.h"
#include "ui_workloads.h"

Workloads::Workloads(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Workloads) {

  ui->setupUi(this);
}

Workloads::~Workloads() { delete ui; }

void Workloads::on_pushButton_clicked() {
  QTextStream message(stdout);
  message << "Programa sera fechado" << Qt::endl;

  QApplication::quit();
}
