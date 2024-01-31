#include "window/addworkloadwindow.h"
#include "ui_addworkloadwindow.h"
#include <context/workload.h>
addWorkloadWindow::addWorkloadWindow(QWidget *parent, Context::MainContext *context) :
      QDialog(parent),
      ui(new Ui::addWorkloadWindow)
{
    this->context = context;
    ui->setupUi(this);
    this->setFixedSize(800,600);
    ui->shape_label->setVisible(false);
    ui->secondValueSpinBox->setVisible(false);

    ui->secondValueSpinBox->setValue(0);
}

addWorkloadWindow::~addWorkloadWindow()
{
    delete ui;
}

void addWorkloadWindow::on_constantRdn_toggled(bool checked)
{
    if(checked)
        workload_type = Context::CONSTANT;
    ui->maxCommSizeSpin->setEnabled(!checked);
    ui->maxProcSizeSpin->setEnabled(!checked);
    ui->maxCommSizeSpin->setValue(ui->minCommSizeSpin->value());
    ui->maxProcSizeSpin->setValue(ui->minProcSizeSpin->value());

}


void addWorkloadWindow::on_minProcSizeSpin_valueChanged(double arg1)
{
    if (ui->constantRdn->isChecked())
    {
        ui->maxProcSizeSpin->setValue(arg1);

    }
}


void addWorkloadWindow::on_minCommSizeSpin_valueChanged(double arg1)
{
    if (ui->constantRdn->isChecked())
        ui->maxCommSizeSpin->setValue(arg1);
}


void addWorkloadWindow::on_poisonRdn_toggled(bool checked)
{
    ui->shape_label->setVisible(!checked);
    ui->secondValueSpinBox->setVisible(!checked);
    if (checked)
        inter_type = Context::POISSON;
}


void addWorkloadWindow::on_weibullRdn_toggled(bool checked)
{
    if(checked)
    {
        ui->lambda_label->setText("Mean");
        ui->shape_label->setVisible(true);
        ui->secondValueSpinBox->setVisible(true);
        inter_type = Context::WEIBULL;
    }
    else
        ui->lambda_label->setText("Lambda");



}
void addWorkloadWindow::on_uniformRdn_toggled(bool checked)
{
    if(checked)
        workload_type = Context::UNIFORM;
}

void addWorkloadWindow::on_okBtn_clicked()
{
    Context::Workload::InterarrivalType *type = new Context::Workload::InterarrivalType();
    type->type = inter_type;
    type->lambda = ui->firstValueSpinBox->value();
    type->shape = ui->secondValueSpinBox->value();

    Context::Workload *workload = new Context::Workload();
    workload->arrivalType = type;
    workload->type = workload_type;
    workload->computingOffload =  ui->computingOffloadSpin->value();
    workload->maxCommSize = ui->maxCommSizeSpin->value();
    workload->maxProcSize = ui->maxProcSizeSpin->value();
    workload->minCommSize = ui->minCommSizeSpin->value();
    workload->minProcSize = ui->minProcSizeSpin->value();
    workload->remainingTasks = ui->numberTasksSPin->value();

    /// temporary
    workload->owner = this->context->users.at(0).name;

    this->context->workloads.push_back(*workload);

    delete workload;
    this->close();




}





void addWorkloadWindow::on_radioButton_toggled(bool checked)
{
    if(checked)
        workload_type = Context::TWO_STAGE_UNIFORM;
}


void addWorkloadWindow::on_exponentialRdn_toggled(bool checked)
{
    ui->shape_label->setVisible(!checked);
    ui->secondValueSpinBox->setVisible(!checked);
    if (checked)
        inter_type = Context::EXPONENTIAL;
}


void addWorkloadWindow::on_fixedRdn_toggled(bool checked)
{
    ui->shape_label->setVisible(!checked);
    ui->secondValueSpinBox->setVisible(!checked);
    if (checked)
        inter_type = Context::FIXED;
}

