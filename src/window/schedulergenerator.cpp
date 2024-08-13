#include "window/schedulergenerator.h"
#include "ui_schedulergenerator.h"
#include <iostream>
#include <QFile>
#include <QMessageBox>

SchedulerGenerator::SchedulerGenerator(QWidget *parent) :
      QMainWindow(parent),
      ui(new Ui::SchedulerGenerator)
{
    ui->setupUi(this);
    disable_operands(true);
    disable_variables(true);

    this->setFixedSize(1350,600);

    connect(ui->cpuCoresBtn, &QPushButton::clicked, this, [=](){
        append_variable("cpuCores");
    });

    connect(ui->cpuProcessingbtn, &QPushButton::clicked, this, [=](){
        append_variable("cpuPP");
    });

    connect(ui->gpuCoreCBtn, &QPushButton::clicked, this, [=](){
        append_variable("gpuCores");
    });

    connect(ui->gpuProcesingPowerBtn, &QPushButton::clicked, this, [=](){
        append_variable("gpuPP");
    });

    connect(ui->taskProcessingSizeBtn, &QPushButton::clicked, this, [=](){
        append_variable("TPS");
    });

    connect(ui->taskCommSizeBtn, &QPushButton::clicked, this, [=](){
        append_variable("TCS");
    });

    connect(ui->taskOffloadingBtn, &QPushButton::clicked, this, [=](){
        append_variable("TOFF");
    });

    connect(ui->RunningMFLOPSbtn, &QPushButton::clicked, this, [=](){
        append_variable("RMFE");
    });

    connect(ui->lastCompletionTimeBtn, &QPushButton::clicked, this, [=](){
        append_variable("LCT");
    });

    connect(ui->constantBtn, &QPushButton::clicked, this, [=](){
        append_variable(ui->constBox->text().replace(",", "."));
    });

    connect(ui->sumBtn, &QPushButton::clicked, this, [=](){
        append_operands("+");
    });
    connect(ui->minusBtn, &QPushButton::clicked, this, [=](){
        append_operands("-");
    });
    connect(ui->divisionBtn, &QPushButton::clicked, this, [=](){
        append_operands("/");
    });
    connect(ui->multiBtn, &QPushButton::clicked, this, [=](){
        append_operands("*");
    });
    connect(ui->openBtn, &QPushButton::clicked, this, [=](){
        append_operands("(");
    });
    connect(ui->closeBtn, &QPushButton::clicked, this, [=](){
        append_operands(")");
        disable_variables(false);
        disable_operands(false);
    });

}

SchedulerGenerator::~SchedulerGenerator()
{
    delete ui;
}

void SchedulerGenerator::change_page(bool backwards)
{
    int curr_page = ui->stackedWidget->currentIndex();

    if (backwards)
        ui->stackedWidget->setCurrentIndex(curr_page -1);
    else
        ui->stackedWidget->setCurrentIndex(curr_page + 1);


}
void SchedulerGenerator::on_stackedWidget_currentChanged(int arg1)
{
    int current_page = ui->stackedWidget->currentIndex();
    disable_bold();
    QListWidgetItem *curr_item = ui->listWidget->item(current_page);
    QFont curr_font = curr_item->font();
    curr_font.setBold(true);
    curr_item->setFont(curr_font);
}


void SchedulerGenerator::on_firstOkBtn_clicked()
{
    this->scheduler_name = ui->nameEdit->toPlainText();

    change_page(false);
}


void SchedulerGenerator::on_secondOkBtn_clicked()
{
    if(ui->staticRdn->isChecked())
    {
        scheduler_type = ui->staticRdn->text();
        ui->lastCompletionTimeBtn->setVisible(false);
    }

    else if(ui->dynamicRdn_2->isChecked())
    {
        scheduler_type = ui->dynamicRdn_2->text();
    }
    else
    {
        QMessageBox::information(nullptr, "Information", "Please select the scheduler's type.");
        this->close();
    }


    change_page(false);
}


void SchedulerGenerator::on_firstBackBtn_clicked()
{
    scheduler_type = "";
    change_page(true);
}


void SchedulerGenerator::disable_bold()
{
    for (int i = 0;  i < ui->listWidget->count(); i++)
    {
        QListWidgetItem *curr_item = ui->listWidget->item(i);
        QFont curr_font = curr_item->font();
        curr_font.setBold(false);
        curr_item->setFont(curr_font);

    }

}
void SchedulerGenerator::disable_variables(bool disable)
{
    ui->cpuCoresBtn->setDisabled(disable);
    ui->cpuProcessingbtn->setDisabled(disable);
    ui->gpuCoreCBtn->setDisabled(disable);
    ui->gpuProcesingPowerBtn->setDisabled(disable);
    ui->taskProcessingSizeBtn->setDisabled(disable);
    ui->taskCommSizeBtn->setDisabled(disable);
    ui->taskOffloadingBtn->setDisabled(disable);
    ui->RunningMFLOPSbtn->setDisabled(disable);
    ui->lastCompletionTimeBtn->setDisabled(disable);
    ui->constantBtn->setDisabled(disable);


}

void SchedulerGenerator::disable_operands(bool disable)
{
    ui->sumBtn->setDisabled(disable);
    ui->minusBtn->setDisabled(disable);
    ui->divisionBtn->setDisabled(disable);
    ui->multiBtn->setDisabled(disable);
    ui->openBtn->setDisabled(disable);
    ui->closeBtn->setDisabled(disable);



}

void SchedulerGenerator::on_incRdn_toggled(bool checked)
{
    ui->formulaLabel->setText("INCREASING");
    formula = "INCREASING";
    disable_variables(false);
    disable_operands(false);
}


void SchedulerGenerator::on_decRdn_toggled(bool checked)
{
    ui->formulaLabel->setText("DECREASING");
    formula = "DECREASING";
    disable_variables(false);
    disable_operands(false);
}


void SchedulerGenerator::on_randomRdn_toggled(bool checked)
{
    ui->formulaLabel->setText("RANDOM");
    disable_variables(true);
    disable_operands(true);
    formula = "RANDOM";
}


void SchedulerGenerator::on_fifoRdn_toggled(bool checked)
{
    ui->formulaLabel->setText("FIFO");
    disable_variables(true);
    disable_operands(true);
    formula = "FIFO";

}

void SchedulerGenerator::append_variable(QString variable)
{
    formula.append(" " + variable);
    disable_variables(true);
    disable_operands(false);
    ui->formulaLabel->setText(formula);
}

void SchedulerGenerator::append_operands(QString operand)
{
    formula.append(" " + operand);
    disable_variables(false);
    disable_operands(true);
    ui->formulaLabel->setText(formula);
}



void SchedulerGenerator::on_eraseBtn_clicked()
{
    QString curr = ui->formulaLabel->text();
    QStringList space = curr.split(' ');
    space.removeLast();
    ui->formulaLabel->setText(space.join(' '));
    formula = ui->formulaLabel->text();
    disable_operands(false);
    disable_variables(false);

}


void SchedulerGenerator::on_secondBackBtn_clicked()
{
    formula = "";
    change_page(true);
}


void SchedulerGenerator::on_thirdOkBtn_clicked()
{
    change_page(false);
}


void SchedulerGenerator::on_thirdBackbtn_clicked()
{
    restriction = " ";
    change_page(true);
}


void SchedulerGenerator::on_lastOkBtn_clicked()
{
    restriction = ui->restrictionSpinBox->text();

    QString general = "SCHEDULER " + scheduler_name.toUpper() +" \n" + "RESTRICT " + restriction + " TASKS PER RESOURCE \n" +
                      scheduler_type.toUpper() + "\n" +formula;

    ui->confirmLbl->setText(general);


    change_page(false);
}


void SchedulerGenerator::on_finishBtn_clicked()
{
    QString prefix;
    if (scheduler_type.toUpper() == "DYNAMIC")
        prefix = "d_";
    else
        prefix = "s_";
    QFile file (prefix + scheduler_name + ".ims");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&file);

        stream << ui->confirmLbl->text();
        file.close();
        QMessageBox::information(this, "Warning","Scheduler generated");
        exit(1);
    }
}


void SchedulerGenerator::on_lastBack_clicked()
{
    ui->confirmLbl->clear();
    change_page(true);
}

