#include "window/simulation.h"
#include "ui_simulation.h"
#include <QFile>
#include <QTextStream>
#include <QTextEdit>
#include <QTableWidget>
#include <QLayout>

Simulation::Simulation(QWidget *parent) :
      QWidget(parent),
      ui(new Ui::Simulation)
{
    ui->setupUi(this);
}

Simulation::~Simulation()
{
    delete ui;
}



