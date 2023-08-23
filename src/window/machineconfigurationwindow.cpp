#include "window/machineconfigurationwindow.h"
#include "ui_machineconfigurationwindow.h"
#include <QSettings>
#include <QDialog>


MachineConfigurationWindow::MachineConfigurationWindow(const QString &iconName, QWidget *parent) :
      QDialog(parent),
      ui(new Ui::MachineConfigurationWindow)
{
    ui->setupUi(this);

    connect(ui->okButton, &QPushButton::clicked, this, &MachineConfigurationWindow::configurationClicked);
    // ui->Owner_ComboBox->addItems(userList);
}

QString MachineConfigurationWindow::getLineEdit01Value()
{
    return ui->labelEdit->text();
}

void MachineConfigurationWindow::setLineEdit01Value(const QString& value)
{
    ui->labelEdit->setText(value);
}

QString MachineConfigurationWindow::getLineEdit02Value()
{
    return ui->CompPower_lineEdit->text();
}

void MachineConfigurationWindow::setLineEdit02Value(const QString& value)
{
    ui->CompPower_lineEdit->setText(value);
}

QString MachineConfigurationWindow::getLineEdit03Value()
{
    return ui->cores_lineEdit->text();
}

void MachineConfigurationWindow::setLineEdit03Value(const QString& value)
{
    ui->cores_lineEdit->setText(value);
}

QString MachineConfigurationWindow::getLineEdit04Value()
{
    return ui->energyconsumer_lineEdit->text();
}

void MachineConfigurationWindow::setLineEdit04Value(const QString& value)
{
    ui->energyconsumer_lineEdit->setText(value);
}


QString MachineConfigurationWindow::getLineEdit05Value()
{
    return ui->lineEdit_4->text();
}

void MachineConfigurationWindow::setLineEdit05Value(const QString& value)
{
    ui->lineEdit_4->setText(value);
}

QString MachineConfigurationWindow::getLineEdit06Value()
{
    return ui->loadFactor_lineEdit->text();
}

void MachineConfigurationWindow::setLineEdit06Value(const QString& value)
{
    ui->loadFactor_lineEdit->setText(value);
}

QString MachineConfigurationWindow::getLineEdit07Value()
{
    return ui->primarystorage_lineEdit->text();
}

void MachineConfigurationWindow::setLineEdit07Value(const QString& value)
{
    ui->primarystorage_lineEdit->setText(value);
}

QString MachineConfigurationWindow::getLineEdit08Value()
{
    return ui->secondaryStorage_lineEdit->text();
}

void MachineConfigurationWindow::setLineEdit08Value(const QString& value)
{
    ui->secondaryStorage_lineEdit->setText(value);
}

int MachineConfigurationWindow::getOwnerComboBoxIndex()
{
    return ui->Owner_ComboBox->currentIndex();
}

void MachineConfigurationWindow::setOwnerComboBoxIndex(int index)
{
    ui->Owner_ComboBox->setCurrentIndex(index);
}

int MachineConfigurationWindow::getSchedulingComboBoxIndex()
{
    return ui->scheduling_comboBox->currentIndex();
}

void MachineConfigurationWindow::setSchedulingComboBoxIndex(int indexschedule)
{
    ui->scheduling_comboBox->setCurrentIndex(indexschedule);
}

bool MachineConfigurationWindow::getCheckBoxState()
{
    return ui->master_checkBox->isChecked();
}

void MachineConfigurationWindow::setCheckBoxState(bool checked)
{
    ui->master_checkBox->setChecked(checked);
}

void MachineConfigurationWindow::addUsersToOwnerComboBox(const QList<QString> &list1Data)
{
    ui->Owner_ComboBox->clear();
    ui->Owner_ComboBox->addItems(list1Data);
}

MachineConfigurationWindow::~MachineConfigurationWindow()
{
    delete ui;
}
