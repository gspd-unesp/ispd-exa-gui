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

QString machineIconConfiguration::getLineEdit01Value()
{
    return ui->labelEdit->text();
}

void machineIconConfiguration::setLineEdit01Value(const QString& value)
{
    ui->labelEdit->setText(value);
}

QString machineIconConfiguration::getLineEdit02Value()
{
    return ui->CompPower_lineEdit->text();
}

void machineIconConfiguration::setLineEdit02Value(const QString& value)
{
    ui->CompPower_lineEdit->setText(value);
}

QString machineIconConfiguration::getLineEdit03Value()
{
    return ui->cores_lineEdit->text();
}

void machineIconConfiguration::setLineEdit03Value(const QString& value)
{
    ui->cores_lineEdit->setText(value);
}

QString machineIconConfiguration::getLineEdit04Value()
{
    return ui->energyconsumer_lineEdit->text();
}

void machineIconConfiguration::setLineEdit04Value(const QString& value)
{
    ui->energyconsumer_lineEdit->setText(value);
}


QString machineIconConfiguration::getLineEdit05Value()
{
    return ui->lineEdit_4->text();
}

void machineIconConfiguration::setLineEdit05Value(const QString& value)
{
    ui->lineEdit_4->setText(value);
}

QString machineIconConfiguration::getLineEdit06Value()
{
    return ui->loadFactor_lineEdit->text();
}

void machineIconConfiguration::setLineEdit06Value(const QString& value)
{
    ui->loadFactor_lineEdit->setText(value);
}

QString machineIconConfiguration::getLineEdit07Value()
{
    return ui->primarystorage_lineEdit->text();
}

void machineIconConfiguration::setLineEdit07Value(const QString& value)
{
    ui->primarystorage_lineEdit->setText(value);
}

QString machineIconConfiguration::getLineEdit08Value()
{
    return ui->secondaryStorage_lineEdit->text();
}

void machineIconConfiguration::setLineEdit08Value(const QString& value)
{
    ui->secondaryStorage_lineEdit->setText(value);
}

// =============================================
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
    return ui->master_checkBox->isChecked();
}

void machineIconConfiguration::setCheckBoxState(bool checked)
{
    ui->master_checkBox->setChecked(checked);
}

machineIconConfiguration::~machineIconConfiguration()
{
    delete ui;
}
