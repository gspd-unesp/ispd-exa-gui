#include "window/machineconfiguration.h"
#include "ui_machineconfiguration.h"
#include <QSettings>
#include <QDialog>

machineIconConfiguration::machineIconConfiguration(const QString &iconName, QWidget *parent) :
      QDialog(parent),
      ui(new Ui::machineIconConfiguration)
{
    ui->setupUi(this);

    connect(ui->okButton, &QPushButton::clicked, this, &machineIconConfiguration::configurationClicked);
}

QString machineIconConfiguration::getLineEditValue()
{
    return ui->labelEdit->text();
}

void machineIconConfiguration::setLineEditValue(const QString& value)
{
    ui->labelEdit->setText(value);
}

int machineIconConfiguration::getComboBoxIndex()
{
    return ui->Owner_ComboBox->currentIndex();
}

void machineIconConfiguration::setComboBoxIndex(int index)
{
    ui->Owner_ComboBox->setCurrentIndex(index);
}

bool machineIconConfiguration::getCheckBoxState()
{
    return ui->checkBox->isChecked();
}

void machineIconConfiguration::setCheckBoxState(bool checked)
{
    ui->checkBox->setChecked(checked);
}

machineIconConfiguration::~machineIconConfiguration()
{
    delete ui;
}
