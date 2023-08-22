#include "scatterplot.h"
#include "ui_scatterplot.h"
#include <QDir>
#include <QFile>
#include <QImage>
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
#include <QPainter>
#include <QSvgRenderer>
#include <QObject>
#include <QEvent>
#include <QVBoxLayout>
#include "qcustomplot.h"

scatterPlot::scatterPlot(QWidget *parent) :
      QWidget(parent),
      ui(new Ui::scatterPlot)
{
    ui->setupUi(this);

    QDir directory(QCoreApplication::applicationDirPath());
    directory.cdUp();


    while (!directory.isRoot())
    {
        if (directory.exists("ispd-exa-gui"))
        {
            qDebug() << "File" << "ispd-exa-gui" << "found in directory:" << directory.absolutePath();
            break;
        }

        directory.cdUp();
    }
    directory.cd("ispd-exa-gui");
    createScatterPlot(directory);
}

scatterPlot::~scatterPlot()
{
    delete ui;
}

void scatterPlot::createScatterPlot(QDir directory)
{
    QFile file("results.json");

    QString fileName = "results.json";
    QString filePath = directory.filePath(fileName);

    qDebug() << "File path to results.json: " << filePath;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QString jsonString = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
    if (!jsonDoc.isObject())
        return;

    QJsonObject jsonObj = jsonDoc.object();

    QCustomPlot *customPlot = new QCustomPlot(this);

    ui->verticalLayout_4->addWidget(customPlot);

    QJsonArray machines = jsonObj["machines"].toArray();

    QVector<double> xData, yData;

    QVector<QColor> dotColors;

    QMap<int, QColor> clusterColorMap;


    for (const QJsonValue &machineValue : machines) {
        QJsonObject machine = machineValue.toObject();
        int id = machine["id"].toInt();
        double mflops = machine["Mflops"].toString().toDouble();
        int scheme = machine["scheme"].toInt();
        yData.append(mflops);
        xData.append(id);

        if (!clusterColorMap.contains(scheme)) {
            QColor newColor = QColor::fromHsv((scheme * 75) % 360, 255, 255);
            clusterColorMap.insert(scheme, newColor);
        }
        dotColors.append(clusterColorMap.value(scheme));

        QCPGraph *pointGraph = customPlot->addGraph();
        pointGraph->setData(QVector<double>() << id, QVector<double>() << mflops);
        pointGraph->setLineStyle(QCPGraph::lsNone);
        pointGraph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, dotColors.last(), Qt::black, 8));


    }

    QVBoxLayout *legendLayout = new QVBoxLayout;
    QVector<int> schemes = clusterColorMap.keys();

    for (int scheme : schemes) {
        QString legendText = QString("Scheme %1").arg(scheme);

        QHBoxLayout *legendItemLayout = new QHBoxLayout;
        QLabel *colorLabel = new QLabel;
        QPixmap colorPixmap(20, 20);
        colorPixmap.fill(clusterColorMap.value(scheme));
        colorLabel->setPixmap(colorPixmap);
        QLabel *textLabel = new QLabel(legendText);

        colorLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        textLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

        legendItemLayout->addWidget(colorLabel);
        legendItemLayout->addWidget(textLabel);

        legendLayout->addLayout(legendItemLayout);
    }

    QWidget *legendWidget = new QWidget;
    legendWidget->setLayout(legendLayout);

    legendWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    ui->verticalLayout_4->addWidget(customPlot);
    ui->verticalLayout_4->addWidget(legendWidget);


    customPlot->xAxis->setLabel("Machine ID");
    customPlot->yAxis->setLabel("Mflops");

    customPlot->rescaleAxes();
    customPlot->replot();


    customPlot->yAxis->setRange(0, customPlot->yAxis->range().upper * 1.1);
    customPlot->xAxis->setRange(0, customPlot->xAxis->range().upper * 1.1);
}
