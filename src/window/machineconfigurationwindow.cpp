#include "window/machineconfigurationwindow.h"
#include "components/conf/machineconfiguration.h"
#include "ui_machineconfigurationwindow.h"
#include <QSettings>
#include <QDialog>
#include <qlineedit.h>


MachineConfigurationWindow::MachineConfigurationWindow(MachineConfiguration *conf, QWidget *parent) :
      QDialog(parent),
      ui(new Ui::MachineConfigurationWindow), conf(conf)
{
    this->ui->setupUi(this);

    connect(this->ui->nameEditLine, &QLineEdit::textChanged, this, &MachineConfigurationWindow::setName);
    this->ui->nameEditLine->setText(QString(this->conf->getName().c_str()));
}

void MachineConfigurationWindow::setName(const QString &newName) {
    this->conf->setName(newName.toStdString());
}
