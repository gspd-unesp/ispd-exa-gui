#include "window/machineconfiguration.h"
#include "ui_machineconfiguration.h"
#include <QSettings>

machineIconConfiguration::machineIconConfiguration(const QString &iconName, QWidget *parent) :
      QWidget(parent),
      ui(new Ui::machineIconConfiguration)
{
    ui->setupUi(this);

}

machineIconConfiguration::~machineIconConfiguration()
{
    delete ui;
}
