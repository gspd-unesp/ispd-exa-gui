#include "window/linkconfigurationwindow.h"
#include "components/conf/linkconfiguration.h"
#include "ui_linkconfigurationwindow.h"
#include <QSettings>
#include <QDialog>
#include <qlineedit.h>
#include <qspinbox.h>


LinkConfigurationWindow::LinkConfigurationWindow(LinkConfiguration *conf, QWidget *parent) :
      QDialog(parent),
      ui(new Ui::LinkConfigurationWindow), conf(conf)
{
    this->ui->setupUi(this);

    connect(this->ui->nameEditLine, &QLineEdit::textChanged, this, &LinkConfigurationWindow::setName);
    connect(this->ui->bandwidthSpinBox, &QSpinBox::valueChanged, this, &LinkConfigurationWindow::setBandwidth);
    connect(this->ui->latencySpinBox, &QDoubleSpinBox::valueChanged, this, &LinkConfigurationWindow::setLatency);
    connect(this->ui->loadFactorSpinBox, &QDoubleSpinBox::valueChanged, this, &LinkConfigurationWindow::setLoadFactor);
    this->ui->nameEditLine->setText(QString(this->conf->getName().c_str()));
}

void LinkConfigurationWindow::setName(const QString &newName) {
    this->conf->setName(newName.toStdString());
}
void LinkConfigurationWindow::setBandwidth(int newBandwidth) {
    this->conf->setBandwidth(newBandwidth);
}
void LinkConfigurationWindow::setLoadFactor(const double newLoadFactor) {
    this->conf->setloadFactor(newLoadFactor);
}
void LinkConfigurationWindow::setLatency(const double newLatency) {
    this->conf->setLatency(newLatency);
}
