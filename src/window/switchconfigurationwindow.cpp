#include "window/switchconfigurationwindow.h"
#include "components/conf/switchconfiguration.h"
#include "ui_switchconfigurationwindow.h"
#include <QDialog>
#include <QSettings>
#include <qlineedit.h>
#include <qspinbox.h>
#include <qt6/QtCore/qglobal.h>

SwitchConfigurationWindow::SwitchConfigurationWindow(SwitchConfiguration *conf,
                                                     QWidget *parent)
    : QDialog(parent), ui(new Ui::SwitchConfigurationWindow), conf(conf)
{
    this->ui->setupUi(this);
    this->setupConfAndWindow();
}

void SwitchConfigurationWindow::setupConfAndWindow()
{
    this->ui->nameEditLine->setText(QString(this->conf->getName().c_str()));
    this->ui->loadFactorSpinBox->setValue(this->conf->getloadFactor());
    this->ui->latencySpinBox->setValue(this->conf->getLatency());
    this->ui->bandwidthSpinBox->setValue(this->conf->getBandwidth());


    connect(this->ui->nameEditLine,
            &QLineEdit::textChanged,
            this,
            &SwitchConfigurationWindow::setName);
    connect(this->ui->bandwidthSpinBox,
            qOverload<int>(&QSpinBox::valueChanged),
            this,
            &SwitchConfigurationWindow::setBandwidth);
    connect(this->ui->latencySpinBox,
            qOverload<double>(&QDoubleSpinBox::valueChanged),
            this,
            &SwitchConfigurationWindow::setLatency);
    connect(this->ui->loadFactorSpinBox,
            qOverload<double>(&QDoubleSpinBox::valueChanged),
            this,
            &SwitchConfigurationWindow::setLoadFactor);
}

void SwitchConfigurationWindow::setName(const QString &newName)
{
    this->conf->setName(newName.toStdString());
}
void SwitchConfigurationWindow::setBandwidth(int newBandwidth)
{
    this->conf->setBandwidth(newBandwidth);
}
void SwitchConfigurationWindow::setLoadFactor(const double newLoadFactor)
{
    this->conf->setloadFactor(newLoadFactor);
}
void SwitchConfigurationWindow::setLatency(const double newLatency)
{
    this->conf->setLatency(newLatency);
}
