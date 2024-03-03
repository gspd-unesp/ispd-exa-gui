#include "window/run_simulation_window.h"
#include <QFileDialog>
#include <QMessageBox>
#include "ui_run_simulation_window.h"
#include <QProcess>

run_simulation_window::run_simulation_window(QWidget *parent) :
      QDialog(parent),
      ui(new Ui::run_simulation_window)
{

    ui->setupUi(this);
    this->setFixedSize(613,286);
}

run_simulation_window::~run_simulation_window()
{
    delete ui;
}

void run_simulation_window::on_rossbuilderBtn_clicked()
{
    QFileDialog fileDialog(this);
    fileDialog.setFileMode(QFileDialog::Directory);
    fileDialog.setOption(QFileDialog::ShowDirsOnly, true);
    fileDialog.setNameFilter("All Files (*);;");

    if (fileDialog.exec())
    {
        QStringList selectedFiles = fileDialog.selectedFiles();
        QString selectedFilePath = selectedFiles.first();
        ui->rossbuilderBtn->setText(selectedFilePath);
    }
}





void run_simulation_window::on_modelBtn_clicked()
{
    QFileDialog fileDialog(this);
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    fileDialog.setNameFilter("JSON Files (*.json)");
    if (fileDialog.exec()){
        QStringList selectedFiles = fileDialog.selectedFiles();
        QString selectedFilePath = selectedFiles.first();
        ui->modelBtn->setText(selectedFilePath);

    }

 }


void run_simulation_window::on_routesBtn_clicked()
{
    QFileDialog fileDialog(this);
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    fileDialog.setNameFilter("ROUTESFiles (*.route)");
    if (fileDialog.exec()){
        QStringList selectedFiles = fileDialog.selectedFiles();
        QString selectedFilePath = selectedFiles.first();
        ui->routesBtn->setText(selectedFilePath);

    }
}


void run_simulation_window::on_okBtn_clicked()
{
    QString path_to_ross = ui->rossbuilderBtn->text();
    QString path_to_json = ui->modelBtn->text();
    QString path_to_route = ui->routesBtn->text();

    QFile sourceJson(path_to_json);
    sourceJson.copy(path_to_ross + "/model.json");

    QFile sourceRoutes(path_to_route);
    sourceRoutes.copy(path_to_ross + "/routes.route");

    if(ui->optimisticRdn->isChecked())
    {
        QString program = "mpirun";
        QStringList arguments;
        int num_process = ui->spinProcess->value();
        arguments << "-np" << QString::number(num_process) << "./ispd" << "--synch=3" << ">" << path_to_ross + "/teste.txt";

        QProcess *process = new QProcess(this);
                process->setWorkingDirectory(path_to_ross);

        QFile outputFile(path_to_ross + "/teste.txt");
        outputFile.open(QIODevice::WriteOnly | QIODevice::Text);

        process->setStandardOutputFile(outputFile.fileName());
        process->start(program, arguments);
        process->waitForFinished();
        this->close();
    }
    else if (ui->conservativeRdn->isChecked())
    {
        QMessageBox message;
        message.critical(0, "Critical Error", "Not suported yet");
    }
    else if(ui->sequentialRdn->isChecked())
    {
        QString program = "./ispd";
        QStringList arguments;

        QProcess *process = new QProcess(this);
        process->setWorkingDirectory(path_to_ross);

        QFile outputFile(path_to_ross + "/teste.txt");
        outputFile.open(QIODevice::WriteOnly | QIODevice::Text);

        process->setStandardOutputFile(outputFile.fileName());
        process->start(program, arguments);
        process->waitForFinished();
        this->close();
    }
    else
    {
        QMessageBox message;
        message.critical(0, "Critical Error", "Select a synchronization method.");
    }

    this->close();

}



