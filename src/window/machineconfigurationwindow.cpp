#include "window/machineconfigurationwindow.h"
#include "components/conf/machineconfiguration.h"
#include "ui_machineconfigurationwindow.h"
#include <QDialog>
#include <QSettings>
#include <qcheckbox.h>
#include <qlineedit.h>
#include <qnamespace.h>
#include <qspinbox.h>

MachineConfigurationWindow::MachineConfigurationWindow(
    MachineConfiguration *conf, QWidget *parent)
    : QDialog(parent), ui(new Ui::MachineConfigurationWindow), conf(conf)
{
    this->ui->setupUi(this);

    this->setupConfAndWindow();
}

void MachineConfigurationWindow::setupConfAndWindow()
{
    this->ui->nameEditLine->setText(this->conf->getName().c_str());
    this->ui->coresSpinBox->setValue(this->conf->coreCount);
    this->ui->computationPowerSpinBox->setValue(this->conf->computationalPower);
    this->ui->loadFactorSpinBox->setValue(this->conf->loadFactor);
    this->ui->gpuCoresSpinBox->setValue(this->conf->gpuCoreCount);
    this->ui->gpuPower->setValue(this->conf->gpuPower);
    this->ui->gpuBandwidth->setValue(this->conf->gpuInterconnectionBandwidth);
    this->ui->ramSpinBox->setValue(this->conf->ram);
    this->ui->diskSpinBox->setValue(this->conf->hardDisk);
    this->ui->energyMaxSpinBox->setValue(this->conf->wattageMax);
    this->ui->energyIdleSpinBox->setValue(this->conf->wattageIdle);
    this->ui->masterCheckBox->setChecked(this->conf->master);
    this->ui->schedulersComboBox->setCurrentText(this->conf->scheduler.c_str());

    connect(this->ui->nameEditLine,
            &QLineEdit::textChanged,
            this,
            &MachineConfigurationWindow::setName);
    connect(this->ui->coresSpinBox,
            qOverload<int>(&QSpinBox::valueChanged),
            this,
            &MachineConfigurationWindow::setCoreCount);
    connect(this->ui->computationPowerSpinBox,
            qOverload<int>(&QSpinBox::valueChanged),
            this,
            &MachineConfigurationWindow::setComputationPower);
    connect(this->ui->loadFactorSpinBox,
            qOverload<double>(&QDoubleSpinBox::valueChanged),
            this,
            &MachineConfigurationWindow::setLoadFactor);
    connect(this->ui->gpuCoresSpinBox,
            qOverload<int>(&QSpinBox::valueChanged),
            this,
            &MachineConfigurationWindow::setGpuCoreCount);
    connect(this->ui->gpuPower,
            qOverload<int>(&QSpinBox::valueChanged),
            this,
            &MachineConfigurationWindow::setGpuPower);
    connect(this->ui->gpuBandwidth,
            qOverload<int>(&QSpinBox::valueChanged),
            this,
            &MachineConfigurationWindow::setGpuBandwidth);
    connect(this->ui->ramSpinBox,
            qOverload<int>(&QSpinBox::valueChanged),
            this,
            &MachineConfigurationWindow::setRam);
    connect(this->ui->diskSpinBox,
            qOverload<int>(&QSpinBox::valueChanged),
            this,
            &MachineConfigurationWindow::setDisk);
    connect(this->ui->masterCheckBox,
            &QCheckBox::stateChanged,
            this,
            &MachineConfigurationWindow::checkMaster);
    connect(this->ui->energyIdleSpinBox,
            qOverload<int>(&QSpinBox::valueChanged),
            this,
            &MachineConfigurationWindow::setWattageIdle);
    connect(this->ui->energyMaxSpinBox,
            qOverload<int>(&QSpinBox::valueChanged),
            this,
            &MachineConfigurationWindow::setWattageMax);
    connect(this->ui->schedulersComboBox,
            &QComboBox::currentTextChanged,
            this,
            &MachineConfigurationWindow::setScheduler);
}

void MachineConfigurationWindow::setRam(const int ram)
{
    this->conf->ram = ram;
}

void MachineConfigurationWindow::setDisk(const int disk)
{
    this->conf->hardDisk = disk;
}

void MachineConfigurationWindow::setWattageIdle(const int wattageIdle)
{
    this->conf->wattageIdle = wattageIdle;
}

void MachineConfigurationWindow::setWattageMax(const int wattageMax)
{
    this->conf->wattageMax = wattageMax;
}

void MachineConfigurationWindow::setScheduler(const QString scheduler)
{
    this->conf->scheduler = scheduler.toStdString();
}

void MachineConfigurationWindow::setComputationPower(const int computationPower)
{
    this->conf->computationalPower = computationPower;
}

void MachineConfigurationWindow::setLoadFactor(const double loadFactor)
{
    this->conf->loadFactor = loadFactor;
}

void MachineConfigurationWindow::setCoreCount(const int coresCount)
{
    this->conf->coreCount = coresCount;
}

void MachineConfigurationWindow::setGpuCoreCount(const int gpuCoreCount)
{
    this->conf->gpuCoreCount = gpuCoreCount;
}

void MachineConfigurationWindow::setGpuBandwidth(const int gpuBandwidth)
{
    this->conf->gpuInterconnectionBandwidth = gpuBandwidth;
}

void MachineConfigurationWindow::setGpuPower(const int gpuPower)
{
    this->conf->gpuPower = gpuPower;
}

void MachineConfigurationWindow::checkMaster(const int checked)
{
    if (checked == Qt::Checked) {
        this->conf->master = true;
    }
    else {
        this->conf->master = false;
    }
}

void MachineConfigurationWindow::setName(const QString &newName)
{
    this->conf->setName(newName.toStdString());
}
