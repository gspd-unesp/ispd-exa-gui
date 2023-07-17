#include "window/simulation.h"
#include "ui_simulation.h"
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QTextEdit>
#include <QTableWidget>
#include <QLayout>
#include <QFileDialog>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QLabel>
#include <QProcess>

Simulation::Simulation(QWidget *parent) :
      QWidget(parent),
      ui(new Ui::Simulation)
{
    ui->setupUi(this);
    createGlobal();
    createTasks();
    createUser();
    createResources();
    createResultsFile();
    resultsCommunication();
    resultsProcessing();
}

Simulation::~Simulation()
{
    delete ui;
}

void Simulation::createGlobal()
{
    /*
    ui->textEdit->clear();
    ui->textEdit->append("                                                                    Simulation Results                  ");
    ui->textEdit->append("");
    ui->textEdit->append("Total Simulated Time = ");
    ui->textEdit->append("Satisfaction = ");
    ui->textEdit->append("Idleness of processing resources = ");
    ui->textEdit->append("Idleness of communication resources = ");
    ui->textEdit->append("Efficiency = ");
    ui->textEdit->append("Efficiency ");
*/
    QString filePath = QCoreApplication::applicationDirPath() + "/results.json";
    QFile file(filePath);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        QString fileContent = stream.readAll();
        file.close();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(fileContent.toUtf8());
        if (!jsonDoc.isNull() && jsonDoc.isObject())
        {
            QJsonObject jsonObj = jsonDoc.object();

            QString totalTime = jsonObj.value("total_simulated_time").toString();
            QString satisfaction = jsonObj.value("satisfaction").toString();
            QString idlenessProcessing = jsonObj.value("idleness_processing").toString();
            QString idlenessCommunication = jsonObj.value("idleness_communication").toString();
            QString efficiency = jsonObj.value("efficiency").toString();

            ui->textEdit->clear();
            ui->textEdit->append("                                                                    Simulation Results                  ");
            ui->textEdit->append("");
            ui->textEdit->append("Total Simulated Time = " + totalTime);
            ui->textEdit->append("Satisfaction = " + satisfaction + " %");
            ui->textEdit->append("Idleness of processing resources = " + idlenessProcessing + " %");
            ui->textEdit->append("Idleness of communication resources = " + idlenessCommunication + " %");
            ui->textEdit->append("Efficiency = " + efficiency + " %");

            int efficiencyValue = efficiency.toDouble();
            if(efficiencyValue > 70.0)
                ui->textEdit->append("Efficiency GOOD");
            else if(efficiencyValue > 40.0)
                ui->textEdit->append("Efficiency MEDIUM");
            else
                ui->textEdit->append("Efficiency BAD");

        }
    }
    else
    {
        ui->textEdit->append("ERRO");
    }

}

void Simulation::createTasks()
{
    /*
    ui->textEdit_2->clear();
    ui->textEdit_2->append("Communication");
    ui->textEdit_2->append("   Queue average time: ");
    ui->textEdit_2->append("   Communication average time: ");
    ui->textEdit_2->append("   System average time: ");
    ui->textEdit_2->append("");
    ui->textEdit_2->append("Processing");
    ui->textEdit_2->append("   Queue average time: ");
    ui->textEdit_2->append("   Processing average time: ");
    ui->textEdit_2->append("   System average time:  ");
*/
    QString filePath = QCoreApplication::applicationDirPath() + "/results.json";
    QFile file(filePath);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        QString fileContent = stream.readAll();
        file.close();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(fileContent.toUtf8());
        if (!jsonDoc.isNull() && jsonDoc.isObject())
        {
            QJsonObject jsonObj = jsonDoc.object();

            QJsonObject communicationObj = jsonObj.value("communication").toObject();
            QString queueAvgTimeComm = communicationObj.value("queue_average_time").toString();
            QString communicationAvgTimeComm = communicationObj.value("communication_average_time").toString();
            QString systemAvgTimeComm = communicationObj.value("system_average_time").toString();

            QJsonObject processingObj = jsonObj.value("processing").toObject();
            QString queueAvgTimeProc = processingObj.value("queue_average_time").toString();
            QString processingAvgTimeProc = processingObj.value("processing_average_time").toString();
            QString systemAvgTimeProc = processingObj.value("system_average_time").toString();

            ui->textEdit_2->clear();
            ui->textEdit_2->append("Communication");
            ui->textEdit_2->append("   Queue average time: " + queueAvgTimeComm + " seconds");
            ui->textEdit_2->append("   Communication average time: " + communicationAvgTimeComm + " seconds");
            ui->textEdit_2->append("   System average time: " + systemAvgTimeComm + " seconds");
            ui->textEdit_2->append("");
            ui->textEdit_2->append("Processing");
            ui->textEdit_2->append("   Queue average time: " + queueAvgTimeProc + " seconds");
            ui->textEdit_2->append("   Processing average time: " + processingAvgTimeProc + " seconds");
            ui->textEdit_2->append("   System average time: " + systemAvgTimeProc + " seconds");
        }
    }
    else
    {
        ui->textEdit_2->append("ERRO");
    }

}

void Simulation::createUser()
{
    /*
    ui->textEdit_3->clear();
    ui->textEdit_3->append("                        User ");
    ui->textEdit_3->append("");
     ui->textEdit_3->append("Number of task: ");
    ui->textEdit_3->append("");
     ui->textEdit_3->append("Communication");
     ui->textEdit_3->append("   Queue average time: ");
     ui->textEdit_3->append("   Communication average time: ");
     ui->textEdit_3->append("   System average time: ");
     ui->textEdit_3->append("");
     ui->textEdit_3->append("Processing");
     ui->textEdit_3->append("   Queue average time: ");
     ui->textEdit_3->append("   Processing average time: ");
     ui->textEdit_3->append("   System average time:  ");
*/
    QString filePath = QCoreApplication::applicationDirPath() + "/results.json";
    qDebug() << "File path: " << filePath;

    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        QString fileContent = stream.readAll();
        file.close();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(fileContent.toUtf8());
        if (!jsonDoc.isNull() && jsonDoc.isObject())
        {
            QJsonObject jsonObj = jsonDoc.object();

            QJsonArray usersArray = jsonObj.value("users").toArray();
            for (int i = 0; i < usersArray.size(); i++)
            {
                QJsonObject userObj = usersArray.at(i).toObject();
                QString userName = userObj.value("name").toString();
                QString numberOfTasks = userObj.value("number_of_tasks").toString();

                QJsonObject communicationObj = userObj.value("communication").toObject();
                QString queueAvgTimeComm = communicationObj.value("queue_average_time").toString();
                QString communicationAvgTimeComm = communicationObj.value("communication_average_time").toString();
                QString systemAvgTimeComm = communicationObj.value("system_average_time").toString();

                QJsonObject processingObj = userObj.value("processing").toObject();
                QString queueAvgTimeProc = processingObj.value("queue_average_time").toString();
                QString processingAvgTimeProc = processingObj.value("processing_average_time").toString();
                QString systemAvgTimeProc = processingObj.value("system_average_time").toString();

                ui->textEdit_3->append("                        User " + userName);
                ui->textEdit_3->append("");
                ui->textEdit_3->append("Number of task: " + numberOfTasks);
                ui->textEdit_3->append("");
                ui->textEdit_3->append("Communication");
                ui->textEdit_3->append("   Queue average time: " + queueAvgTimeComm + " seconds");
                ui->textEdit_3->append("   Communication average time: " + communicationAvgTimeComm + " seconds");
                ui->textEdit_3->append("   System average time: " + systemAvgTimeComm + " seconds");
                ui->textEdit_3->append("");
                ui->textEdit_3->append("Processing");
                ui->textEdit_3->append("   Queue average time: " + queueAvgTimeProc + " seconds");
                ui->textEdit_3->append("   Processing average time: " + processingAvgTimeProc + " seconds");
                ui->textEdit_3->append("   System average time:  " + systemAvgTimeProc + " seconds");
                ui->textEdit_3->append("");
            }
        }
    }
    else
    {
        ui->textEdit_3->append("ERRO");
    }
}



void Simulation::on_pushButton_clicked()
{

}

void Simulation::createResources()
{
    ui->tableWidget->setColumnWidth(2, 194);
    ui->tableWidget->setColumnWidth(3, 195);

           //----------------------------------------------------------------------------------------------------

    QPixmap image(":/icons/save.png");
    QSize imageSize(30, 30);
    QPixmap resizedImage = image.scaled(imageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);


    ui->pushButton->setIcon(QIcon(resizedImage));
    ui->pushButton->setIconSize(imageSize);

    ui->pushButton->setFixedSize(115, 40);

    connect(ui->pushButton, &QPushButton::clicked, this, &Simulation::on_pushButton_clicked);

    //----------------------------------------------------------------------------------------

    QString filePath = QCoreApplication::applicationDirPath() + "/results.json";
    QFile file(filePath);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        QString fileContent = stream.readAll();
        file.close();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(fileContent.toUtf8());
        if (!jsonDoc.isNull() && jsonDoc.isObject())
        {
            QJsonObject jsonObj = jsonDoc.object();

            QJsonArray machineArray = jsonObj.value("machines").toArray();
            QJsonArray linksArray = jsonObj.value("links").toArray();

            int rowCount = machineArray.size() + linksArray.size();

                   // Set the number of rows in the table widget
            ui->tableWidget->setRowCount(rowCount);

            int rowIndex = 0;

                   // Iterate over the machine items
            for (const QJsonValue& machineValue : machineArray)
            {
                QJsonObject machineObj = machineValue.toObject();
                QString label = machineObj.value("label").toString();
                QString owner = machineObj.value("owner").toString();
                QString processingPerformed = machineObj.value("processing_performed").toString();
                QString communicationPerformed = machineObj.value("communication_performed").toString();

                       // Set the values in the table widget
                ui->tableWidget->setItem(rowIndex, 0, new QTableWidgetItem(label));
                ui->tableWidget->setItem(rowIndex, 1, new QTableWidgetItem(owner));
                ui->tableWidget->setItem(rowIndex, 2, new QTableWidgetItem(processingPerformed));
                ui->tableWidget->setItem(rowIndex, 3, new QTableWidgetItem(communicationPerformed));

                rowIndex++;
            }

                  // Iterate over the links items
            for (const QJsonValue& linksValue : linksArray)
            {
                QJsonObject linksObj = linksValue.toObject();
                QString label = linksObj.value("label").toString();
                QString processingPerformed = linksObj.value("processing_performed").toString();
                QString communicationPerformed = linksObj.value("communication_performed").toString();

                       // Set the values in the table widget
                ui->tableWidget->setItem(rowIndex, 0, new QTableWidgetItem(label));
                ui->tableWidget->setItem(rowIndex, 2, new QTableWidgetItem(processingPerformed));
                ui->tableWidget->setItem(rowIndex, 3, new QTableWidgetItem(communicationPerformed));

                rowIndex++;
            }
        }
    }
    else
    {
        qDebug() << "Failed to open file: " << file.errorString();
    }
}

void Simulation::createResultsFile()
{
    QString filePath = QCoreApplication::applicationDirPath() + "/results.json";
    QFile file(filePath);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        QString fileContent = stream.readAll();
        file.close();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(fileContent.toUtf8());
        if (!jsonDoc.isNull() && jsonDoc.isObject())
        {
            QJsonObject jsonObj = jsonDoc.object();

                   // Retrieve the machine and link arrays from the JSON object
            QJsonArray machineArray = jsonObj.value("machines").toArray();
            QJsonArray linkArray = jsonObj.value("links").toArray();

            QString machineFilePath = QCoreApplication::applicationDirPath() + "/machine_values.txt";
            QString linkFilePath = QCoreApplication::applicationDirPath() + "/link_values.txt";

                   // Create a QString to store the machine values
            QString machineValues;

            for (const QJsonValue& machineValue : machineArray)
            {
                QJsonObject machineObj = machineValue.toObject();
                QString label = machineObj.value("label").toString();
                QString mflops = machineObj.value("Mflops").toString();

                       // Append label and Mflops values to the machine values string
                machineValues += mflops + "_" + label + "\n";
            }

                   // Save the machine values to a file
            QFile machineFile(machineFilePath);
            if (machineFile.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QTextStream machineStream(&machineFile);
                machineStream << machineValues;
                machineFile.close();
            }

                   // Create a QString to store the link values
            QString linkValues;

            for (const QJsonValue& linkValue : linkArray)
            {
                QJsonObject linkObj = linkValue.toObject();
                QString label = linkObj.value("label").toString();
                QString mbits = linkObj.value("Mbits").toString();

                       // Append label and Mbits values to the link values string
                linkValues += mbits + "_" + label + "\n";
            }

                   // Save the link values to a file
            QFile linkFile(linkFilePath);
            if (linkFile.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QTextStream linkStream(&linkFile);
                linkStream << linkValues;
                linkFile.close();
            }
        }
    }
    else
    {
    }
}

void Simulation::resultsCommunication()
{
    QString filePath = QCoreApplication::applicationDirPath() + "/link_values.txt";
    QString command = QString("./packCircles -i %1 > output.svg -c").arg(filePath);
    QProcess::execute(command);

           // Load the SVG image and display it in the QLabel
    QPixmap pixmap("output.svg");
    ui->label->setPixmap(pixmap);
    ui->label->adjustSize();
}

void Simulation::resultsProcessing()
{
    QString filePath = QCoreApplication::applicationDirPath() + "/machine_values.txt";
    QString command = QString("./packCircles -i %1 > output_2.svg -c").arg(filePath);
    QProcess::execute(command);

           // Load the SVG image and display it in the QLabel
    QPixmap pixmap("output_2.svg");
    ui->label_2->setPixmap(pixmap);
    ui->label_2->adjustSize();
}
