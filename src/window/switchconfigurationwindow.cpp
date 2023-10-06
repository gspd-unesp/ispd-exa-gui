#include "window/switchconfigurationwindow.h"
#include "components/conf/switchconfiguration.h"
#include "ui_switchconfigurationwindow.h"
#include <QDialog>
#include <QSettings>
#include <qlineedit.h>
#include <qspinbox.h>

SwitchConfigurationWindow::SwitchConfigurationWindow(SwitchConfiguration *conf,
                                                     QWidget *parent)
    : QDialog(parent), ui(new Ui::SwitchConfigurationWindow), conf(conf)
{
    this->ui->setupUi(this);

    connect(this->ui->nameEditLine,
            &QLineEdit::textChanged,
            this,
            &SwitchConfigurationWindow::setName);
    connect(this->ui->bandwidthSpinBox,
            &QSpinBox::valueChanged,
            this,
            &SwitchConfigurationWindow::setBandwidth);
    connect(this->ui->latencySpinBox,
            &QDoubleSpinBox::valueChanged,
            this,
            &SwitchConfigurationWindow::setLatency);
    connect(this->ui->loadFactorSpinBox,
            &QDoubleSpinBox::valueChanged,
            this,
            &SwitchConfigurationWindow::setLoadFactor);
    this->ui->nameEditLine->setText(QString(this->conf->getName().c_str()));
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
