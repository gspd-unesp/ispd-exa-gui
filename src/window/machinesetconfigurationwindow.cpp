#include "window/machinesetconfigurationwindow.h"
#include "components/conf/machinesetconfiguration.h"
#include "ui_machinesetconfigurationwindow.h"
#include <QSettings>
#include <QDialog>
#include <qlineedit.h>
#include <qspinbox.h>


MachineSetConfigurationWindow::MachineSetConfigurationWindow(MachineSetConfiguration *conf, QWidget *parent) :
      QDialog(parent),
      ui(new Ui::MachineSetConfigurationWindow), conf(conf)
{
    this->ui->setupUi(this);

    this->ui->nameEditLine->setText(QString(this->conf->getName().c_str()));
}

void MachineSetConfigurationWindow::setName(const QString &newName) {
    this->conf->setName(newName.toStdString());
}
void MachineSetConfigurationWindow::setBandwidth(int newBandwidth) {
    this->conf->setBandwidth(newBandwidth);
}
void MachineSetConfigurationWindow::setLoadFactor(const double newLoadFactor) {
    this->conf->setloadFactor(newLoadFactor);
}
void MachineSetConfigurationWindow::setLatency(const double newLatency) {
    this->conf->setLatency(newLatency);
}
