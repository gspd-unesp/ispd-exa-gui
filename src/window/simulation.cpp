#include "window/simulation.h"
#include "ui_simulation.h"
#include <QFile>
#include <QDir>
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

//CIRCLE PACKING
#include "packCircles.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <getopt.h>


void usage(char *progname)
{
    fprintf(stderr, "Usage:\n  %s -i FILENAME\n", progname);
    fprintf(stderr, "\n");
    fprintf(stderr, "Mandatory arguments:\n");
    fprintf(stderr, "   -i FILENAME   Name of input file\n");
    fprintf(stderr, "\n");
    exit(EXIT_FAILURE);
}

static void hsv2rgb(double h, double s, double v, unsigned int *r, unsigned int *b, unsigned int *g)
{

    if (s == 0.0)
    {
        *r = (unsigned int)floor(v * 256);
        *g = (unsigned int)floor(v * 256);
        *b = (unsigned int)floor(v * 256);
        return;
    }

    int i = (int)floor(h * 6);
    double f = h * 6 - i;
    double p = v * (1 - s);
    double q = v * (1 - s * f);
    double t = v * (1 - s * (1 - f));

    if (i == 0)
    {
        *r = (unsigned int)floor(v * 256);
        *g = (unsigned int)floor(t * 256);
        *b = (unsigned int)floor(p * 256);
    }
    else if (i == 1)
    {
        *r = (unsigned int)floor(q * 256);
        *g = (unsigned int)floor(v * 256);
        *b = (unsigned int)floor(p * 256);
    }
    else if (i == 2)
    {
        *r = (unsigned int)floor(p * 256);
        *g = (unsigned int)floor(v * 256);
        *b = (unsigned int)floor(t * 256);
    }
    else if (i == 3)
    {
        *r = (unsigned int)floor(p * 256);
        *g = (unsigned int)floor(q * 256);
        *b = (unsigned int)floor(v * 256);
    }
    else if (i == 4)
    {
        *r = (unsigned int)floor(t * 256);
        *g = (unsigned int)floor(p * 256);
        *b = (unsigned int)floor(v * 256);
    }
    else
    {
        *r = (unsigned int)floor(v * 256);
        *g = (unsigned int)floor(p * 256);
        *b = (unsigned int)floor(q * 256);
    }
}

static void printSVG(node_t *first, node_t *a_, node_t *bb_topright, node_t *bb_bottomleft, int debug, FILE *output_file)
{
    double spacing = MAX(bb_topright->y + fabs(bb_bottomleft->y), bb_topright->x + fabs(bb_bottomleft->x)) / 400.0;
    double height = (bb_topright->y + fabs(bb_bottomleft->y)) + 2 * spacing;
    double width = (bb_topright->x + fabs(bb_bottomleft->x)) + 2 * spacing;
    int viewport_width = 640;
    int viewport_height = 480;
    double stroke_width = viewport_width / 400 * (width / viewport_width);

    fprintf(output_file, "<svg xmlns=\"http://www.w3.org/2000/svg\" height=\"%i\" width=\"%i\" viewBox=\"0 0 %.5f %.5f\" preserveAspectRatio=\"xMidYMid meet\">\n", viewport_height, viewport_width, width, height);
    fprintf(output_file, "<defs>\n");
    fprintf(output_file, "<style type=\"text/css\"><![CDATA[\n");
    fprintf(output_file, "  .circle_c { fill:#eee; stroke: #444; stroke-width: %.5f }\n", stroke_width);

    fprintf(output_file, "  .text_c { text-anchor: middle; dominant-baseline: central; }\n");

    fprintf(output_file, "]]></style>\n");
    fprintf(output_file, "</defs>\n");
    fprintf(output_file, "<g transform=\"translate(%.5f,%.5f)\">\n", (width) / 2.0, (height) / 2.0);

    double offset_x = (bb_bottomleft->x + bb_topright->x) / 2.0;
    double offset_y = (bb_bottomleft->y + bb_topright->y) / 2.0;

    node_t* n = first;
    while (n)
    {
        n->x -= offset_x;
        n->y -= offset_y;
        fprintf(output_file, "<g><title>%s (num=%i)</title><circle cx=\"%.5f\" cy=\"%.5f\" r=\"%.5f\" style=\"fill:%s\" class=\"circle_c\"/></g>\n", n->name ? n->name : "", (int)n->size, n->x, n->y, n->radius, n->color ? n->color : "");

        double fontSize = n->radius * 0.25;

        double textX = n->x;
        double textY = n->y + fontSize * 0.35;

        fprintf(output_file, "<text x=\"%.5f\" y=\"%.5f\" class=\"text_c\" style=\"font-size: %.5fpx; dominant-baseline: middle; text-anchor: middle;\">%s</text>\n", textX, textY, fontSize, n->name ? n->name : "");

        node_t* next = n->insertnext;
        n = next;
    }

    if (debug && a_ && a_->next)
    {
        node_t *a = a_;
        node_t *b = a_->next;
        do
        {
            fprintf(output_file, "<line x1=\"%.5f\" y1=\"%.5f\" x2=\"%.5f\" y2=\"%.5f\" style=\"stroke:black;stroke-width:%.1f;\" />\n", a->x, a->y, b->x, b->y, stroke_width);
            a = b;
            b = b->next;
        } while (b != a_->next);
    }
    fprintf(output_file, "</g>\n");
    fprintf(output_file, "</svg>\n");
}

static node_t *alloc_node(unsigned long size_, int num_)
{
    node_t *n = (node_t *)malloc(sizeof(node_t));
    n->size = size_;

    double r = sqrt((double)size_ / M_PI);
    n->radius = r;
    n->next = NULL;
    n->prev = NULL;
    n->insertnext = NULL;
    n->color = NULL;
    n->name = NULL;
    n->x = 0.0;
    n->y = 0.0;
    n->num = num_;
    return n;
}

static void bound(node_t *n, node_t *topright, node_t *bottomleft)
{
    bottomleft->x = MIN(n->x - n->radius, bottomleft->x);
    bottomleft->y = MIN(n->y - n->radius, bottomleft->y);
    topright->x = MAX(n->x + n->radius, topright->x);
    topright->y = MAX(n->y + n->radius, topright->y);
}

static double distance(node_t *a)
{
    return sqrt(a->x * a->x + a->y * a->y);
}

static void place(node_t *a, node_t *b, node_t *c)
{
    double da = b->radius + c->radius;
    double db = a->radius + c->radius;
    double dx = b->x - a->x;
    double dy = b->y - a->y;
    double dc = sqrt(dx * dx + dy * dy);
    if (dc > 0.0)
    {
        double cos = (db * db + dc * dc - da * da) / (2 * db * dc);
        double theta = acos(cos);
        double x = cos * db;
        double h = sin(theta) * db;
        dx /= dc;
        dy /= dc;
        c->x = a->x + x * dx + h * dy;
        c->y = a->y + x * dy - h * dx;
    }
    else
    {
        c->x = a->x + db;
        c->y = a->y;
    }
}

static int intersects(node_t *a, node_t *b)
{
    double dx = b->x - a->x;
    double dy = b->y - a->y;
    double dr = a->radius + b->radius;
    if (dr * dr - 1e-6 > dx * dx + dy * dy)
        return 1;
    else
        return 0;
}

static void insert(node_t *a, node_t *b)
{
    node_t *c = a->next;
    a->next = b;
    b->prev = a;
    b->next = c;
    if (c)
        c->prev = b;
}

static void splice(node_t *a, node_t *b)
{
    a->next = b;
    b->prev = a;
}

static node_t *placeCircles(node_t *firstnode, node_t *bb_topright, node_t *bb_bottomleft, int debug)
{


    node_t *a = firstnode;
    node_t *b = NULL;
    node_t *c = NULL;

    a->x = -1 * a->radius;
    bound(a, bb_topright, bb_bottomleft);


    if (!a->insertnext)
    {
        return a;
    }
    b = a->insertnext;
    b->x = b->radius;
    b->y = 0;
    bound(b, bb_topright, bb_bottomleft);


    if (!b->insertnext)
    {
        return a;
    }
    c = b->insertnext;
    place(a, b, c);
    bound(c, bb_topright, bb_bottomleft);

    if (!c->insertnext)
    {
        return a;
    }


    a->next = c;
    a->prev = b;
    b->next = a;
    b->prev = c;
    c->next = b;
    c->prev = a;
    b = c;


    int skip = 0;
    c = c->insertnext;
    while (c)
    {
        if (debug)
            fprintf(stderr, "Inserting node %i ------------------------\n", c->num);


        if (!skip)
        {
            node_t *n = a;
            node_t *nearestnode = n;
            double nearestdist = FLT_MAX;
            do
            {
                double dist_n = distance(n);
                if (dist_n < nearestdist)
                {
                    nearestdist = dist_n;
                    nearestnode = n;
                }
                n = n->next;
            } while (n != a);

            if (debug)
                fprintf(stderr, "Node %i is nearest to the origin\n", nearestnode->num);
            a = nearestnode;
            b = nearestnode->next;
            skip = 0;
        }

        if (debug)
            fprintf(stderr, "Trying to place node %i between nodes %i and %i\n", c->num, a->num, b->num);


        place(a, b, c);


        int isect = 0;
        node_t *j = b->next;
        node_t *k = a->prev;
        double sj = b->radius;
        double sk = a->radius;

        do
        {
            if (sj <= sk)
            {
                if (debug)
                    fprintf(stderr, "forw: testing intersection of nodes %i and %i\n", c->num, j->num);
                if (intersects(j, c))
                {
                    if (debug)
                        fprintf(stderr, "Node %i intersects with node %i\n", c->num, j->num);
                    splice(a, j);
                    b = j;
                    skip = 1;
                    isect = 1;
                    break;
                }
                sj += j->radius;
                j = j->next;
            }
            else
            {
                if (debug)
                    fprintf(stderr, "back: testing intersection of nodes %i and %i\n", c->num, k->num);
                if (intersects(k, c))
                {
                    if (debug)
                        fprintf(stderr, "Node %i intersects with node %i\n", c->num, k->num);
                    splice(k, b);
                    a = k;
                    skip = 1;
                    isect = 1;
                    break;
                }
                sk += k->radius;
                k = k->prev;
            }
        } while (j != k->next);

        if (isect == 0)
        {

            insert(a, c);
            b = c;
            bound(c, bb_topright, bb_bottomleft);
            skip = 0;
            c = c->insertnext;
        }
    }

    return a;
}


Simulation::Simulation(QWidget *parent) :
      QWidget(parent),
      ui(new Ui::Simulation)
{
    ui->setupUi(this);

    QDir directory(QCoreApplication::applicationDirPath());
    directory.cdUp();
    directory.cdUp();
    directory.cdUp();
    directory.cdUp();
    directory.cdUp();
    directory.cdUp();
    directory.cd("ispd-exa-gui");

    originalTextEditPos = ui->textEdit->pos();
    originalTextEditSize = ui->textEdit->size();
    originalLabelPos = ui->label->pos();
    originalLabelSize = ui->label->size();


    QApplication::instance()->installEventFilter(this);

    createGlobal(directory);
    createTasks(directory);
    createUser(directory);
    createResources(directory);
    createResultsFile(directory);
    resultsCommunication(directory);
    resultsProcessing(directory);
    createStackedLineGraph(directory);

}

Simulation::~Simulation()
{
    delete ui;
}

void Simulation::createGlobal(QDir directory)
{

    QString fileName = "results.json";

    QString filePath = directory.filePath(fileName);

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

void Simulation::createTasks(QDir directory)
{

    QString fileName = "results.json";

    QString filePath = directory.filePath(fileName);
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

void Simulation::createUser(QDir directory)
{

    QString fileName = "results.json";
   QString filePath = directory.filePath(fileName);

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
                QString userName = userObj.value("label").toString();
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

void Simulation::createResources(QDir directory)
{
    ui->tableWidget->setColumnWidth(2, 184);
    ui->tableWidget->setColumnWidth(3, 185);

           //----------------------------------------------------------------------------------------------------

    QPixmap image(":/icons/save.png");
    QSize imageSize(30, 30);
    QPixmap resizedImage = image.scaled(imageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);


    ui->pushButton->setIcon(QIcon(resizedImage));
    ui->pushButton->setIconSize(imageSize);

    ui->pushButton->setFixedSize(115, 40);

    connect(ui->pushButton, &QPushButton::clicked, this, &Simulation::on_pushButton_clicked);

    //----------------------------------------------------------------------------------------


   QString fileName = "results.json";


   QString filePath = directory.filePath(fileName);
    //QFile file(filePath);

           //QString filePath = QCoreApplication::applicationDirPath() + "/results.json";
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

            QJsonArray machineArray = jsonObj.value("machines").toArray();
            QJsonArray linksArray = jsonObj.value("links").toArray();

            int rowCount = machineArray.size() + linksArray.size();

            ui->tableWidget->setRowCount(rowCount);

            int rowIndex = 0;

            for (const QJsonValue& machineValue : machineArray)
            {
                QJsonObject machineObj = machineValue.toObject();
                QString label = machineObj.value("label").toString();
                QString owner = machineObj.value("owner").toString();
                QString processingPerformed = machineObj.value("processing_performed").toString();
                QString communicationPerformed = machineObj.value("communication_performed").toString();

                ui->tableWidget->setItem(rowIndex, 0, new QTableWidgetItem(label));
                ui->tableWidget->setItem(rowIndex, 1, new QTableWidgetItem(owner));
                ui->tableWidget->setItem(rowIndex, 2, new QTableWidgetItem(processingPerformed));
                ui->tableWidget->setItem(rowIndex, 3, new QTableWidgetItem(communicationPerformed));

                rowIndex++;
            }

            for (const QJsonValue& linksValue : linksArray)
            {
                QJsonObject linksObj = linksValue.toObject();
                QString label = linksObj.value("label").toString();
                QString processingPerformed = linksObj.value("processing_performed").toString();
                QString communicationPerformed = linksObj.value("communication_performed").toString();

                ui->tableWidget->setItem(rowIndex, 0, new QTableWidgetItem(label));

                ui->tableWidget->setItem(rowIndex, 1, new QTableWidgetItem("---"));

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

void Simulation::createResultsFile(QDir directory)
{


   QString fileName = "results.json";


    QString filePath = directory.filePath(fileName);
    //QFile file(filePath);

           //QString filePath = QCoreApplication::applicationDirPath() + "/results.json";

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
            QJsonArray linkArray = jsonObj.value("links").toArray();

            QString machines = "machine_values.txt";
            QString links = "link_values.txt";

            //QString machineFilePath = QCoreApplication::applicationDirPath() + "/machine_values.txt";
            //QString linkFilePath = QCoreApplication::applicationDirPath() + "/link_values.txt";
             QString machineFilePath = directory.filePath(machines);
             QString linkFilePath = directory.filePath(links);


            QString machineValues;

            for (const QJsonValue& machineValue : machineArray)
            {
                QJsonObject machineObj = machineValue.toObject();
                QString label = machineObj.value("label").toString();
                QString mflops = machineObj.value("Mflops").toString();

                machineValues += mflops + "_" + label + "\n";
            }

            QFile machineFile(machineFilePath);
            if (machineFile.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QTextStream machineStream(&machineFile);
                machineStream << machineValues;
                machineFile.close();
            }

            QString linkValues;

            for (const QJsonValue& linkValue : linkArray)
            {
                QJsonObject linkObj = linkValue.toObject();
                QString label = linkObj.value("label").toString();
                QString mbits = linkObj.value("Mbits").toString();

                linkValues += mbits + "_" + label + "\n";
            }

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

void Simulation::resultsCommunication(QDir directory)
{

    circlePacking(1, directory);

    QPixmap pixmap("output.svg");
    ui->label->setPixmap(pixmap);
    ui->label->adjustSize();
}
void Simulation::resultsProcessing(QDir directory)
{


    circlePacking(2, directory);

    QPixmap pixmap("output_2.svg");
    ui->label_2->setPixmap(pixmap);
    ui->label_2->adjustSize();
}

void Simulation::circlePacking(int flag, QDir directory)
{


    QString filePath = directory.absolutePath();
    QDir::setCurrent(filePath);

    char *inputfilename;;
    if(flag == 1)
        inputfilename = "link_values.txt";
    else if(flag == 2)
        inputfilename = "machine_values.txt";

    int debug = 0;
    int generate_colors = 1;

    node_t *firstnode = NULL;
    node_t *lastinsertednode = NULL;

    node_t *bb_bottomleft = alloc_node(0, -1);
    bb_bottomleft->y = (double)INT_MAX;
    bb_bottomleft->x = (double)INT_MAX;
    node_t *bb_topright = alloc_node(0, -1);
    bb_topright->y = (double)INT_MIN;
    bb_topright->x = (double)INT_MIN;

    FILE *fp = fopen(inputfilename, "r");
    if (!fp)
    {
        fprintf(stderr, "Could not open file %s\n", inputfilename);
        exit(EXIT_FAILURE);
    }

    int num_circles = 0;
    int counter = 0;
    srand((unsigned int)time(NULL));
    double h = generate_colors ? (double)rand() / (double)(RAND_MAX) : 0.0;
    char *line = NULL;
    size_t size = 0;
    ssize_t length_line;
    while ((length_line = getline(&line, &size, fp)) != -1)
    {
        if (length_line == 1)
        {
            continue;
        }
        unsigned long input_number = ULONG_MAX;
        input_number = strtoul(line, NULL, 10);
        if (input_number == 0 || input_number == ULONG_MAX)
        {
            //fprintf(stderr, "Bad number (out of range error) in input line: %s", line);
            //exit(EXIT_FAILURE);
            continue;
        }

        node_t *n = alloc_node(input_number, counter);
        if (!firstnode)
        {
            firstnode = n;
            lastinsertednode = n;
        }
        else
        {
            lastinsertednode->insertnext = n;
            lastinsertednode = n;
        }
        counter++;
        char *underscore = strchr(line, '_');
        if (underscore)
        {
            *underscore = '\0';
            char *name = underscore + 1;
            char *newline = strchr(name, '\n');
            if (newline)
                *newline = '\0';
            n->name = strdup(name);
        }

        if (generate_colors && n->color == NULL)
        {
            unsigned int r, g, b;
            hsv2rgb(h, 0.5, 0.95, &r, &g, &b);
            h += 0.618033988749895;
            h = fmod(h, 1);
            char *color = (char *)malloc(sizeof(char) * 17);
            color[16] = '\0';
            sprintf(color, "rgb(%.3u,%.3u,%.3u)", r, g, b);
            n->color = color;
        }
    }
    free(line);
    fclose(fp);
    num_circles = counter;


    node_t *a = placeCircles(firstnode, bb_topright, bb_bottomleft, debug);



    FILE* output_file;
    if(flag == 1)
        output_file = fopen("output.svg", "w");
    else if(flag == 2)
        output_file = fopen("output_2.svg", "w");

    printSVG(firstnode, a, bb_topright, bb_bottomleft, debug, output_file);


    node_t *n = firstnode;
    while (n)
    {
        node_t *next = n->insertnext;
        free(n->name);
        free(n->color);
        free(n);
        n = next;
    }
    free(bb_bottomleft);
    free(bb_topright);
    fclose(output_file);

    return;
}

bool Simulation::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::WindowStateChange)
    {
        Qt::WindowStates states = this->windowState();
        bool isFullScreen = (states & Qt::WindowFullScreen);


        if (isFullScreen)
        {
            int windowWidth = this->width();
            int windowHeight = this->height();

            int newX = (windowWidth - 800) / 2;
            int newY = ((windowHeight - 600) / 2);

            ui->textEdit->move(newX, newY);
            ui->textEdit->resize(800, 600);

            ui->textEdit_2->move(newX, newY);
            ui->textEdit_2->resize(800, 600);

            ui->textEdit_3->move(newX, newY);
            ui->textEdit_3->resize(800, 600);

            ui->tableWidget->move(newX, newY);
            ui->tableWidget->resize(800, 600);
            ui->tableWidget->setColumnWidth(2, 275);
            ui->tableWidget->setColumnWidth(3, 300);

            ui->label_2->move(newX, newY);
            ui->label_2->resize(800, 600);
            QPixmap pixmap_2("output_2.svg");
            ui->label_2->setPixmap(pixmap_2);
            ui->label_2->adjustSize();
            /*

            QPixmap originalPixmap_2("output_2.svg");

            int newWidth = 800;

            int newHeight = originalPixmap_2.scaledToWidth(newWidth).height();

            QPixmap resizedPixmap_2 = originalPixmap_2.scaled(newWidth, newHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);

            ui->label_2->setPixmap(resizedPixmap_2);
            ui->label_2->move(newX, newY);
*/
//------------------------------------------------------------------------------------------------------------------------


            ui->label->move(newX, newY);
            ui->label->resize(800, 600);
            QPixmap pixmap("output.svg");
            ui->label->setPixmap(pixmap);
            ui->label->adjustSize();
/*
            QPixmap originalPixmap("output.svg");


            QPixmap resizedPixmap = originalPixmap.scaled(newWidth, newHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);

            ui->label->setPixmap(resizedPixmap);
            ui->label->move(newX, newY);
            */
        }
        else
        {

            ui->textEdit->move(originalTextEditPos);
            ui->textEdit->resize(originalTextEditSize);

            ui->textEdit_2->move(originalTextEditPos);
            ui->textEdit_2->resize(originalTextEditSize);

            ui->textEdit_3->move(originalTextEditPos);
            ui->textEdit_3->resize(originalTextEditSize);

            ui->tableWidget->move(originalTextEditPos);
            ui->tableWidget->resize(originalTextEditSize);
            ui->tableWidget->setColumnWidth(2, 184);
            ui->tableWidget->setColumnWidth(3, 185);

            ui->label->move(originalLabelPos);
            ui->label->resize(originalLabelSize);

            ui->label_2->move(originalLabelPos);
            ui->label_2->resize(originalLabelSize);

            QPixmap pixmap("output.svg");
            ui->label->setPixmap(pixmap);
            ui->label->adjustSize();

            QPixmap pixmap_2("output_2.svg");
            ui->label_2->setPixmap(pixmap_2);
            ui->label_2->adjustSize();


        }
    }

    return QWidget::eventFilter(obj, event);
}


void Simulation::createStackedLineGraph(QDir directory)
{
    QFile file("results.json");

    QString fileName = "results.json";
    QString filePath = directory.filePath(fileName);

    qDebug() << "File path of results.json: " << filePath;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QString jsonString = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
    if (!jsonDoc.isObject())
        return;

    QJsonObject jsonObj = jsonDoc.object();

    QCustomPlot *customPlotUsers = new QCustomPlot(this);
    QCustomPlot *customPlotMachines = new QCustomPlot(this);
    QCustomPlot *customPlotTasks = new QCustomPlot(this);

    ui->verticalLayout_2->addWidget(customPlotUsers);
    ui->verticalLayout_3->addWidget(customPlotMachines);
    ui->verticalLayout->addWidget(customPlotTasks);

    QVector<QColor> lineColors = {
        Qt::red,
        Qt::blue,
        Qt::green,
        Qt::cyan,
        Qt::magenta,
        Qt::yellow
    };

        auto createGraphs = [lineColors](QCustomPlot* customPlot, const QJsonArray& dataArray, const QString& yAxisLabel) {

        QVector<QCPGraph*> graphs;
        QVector<double> cumulativeYData(dataArray.size(), 0.0);

        for (int i = 0; i < dataArray.size(); ++i)
        {
            QJsonObject item = dataArray.at(i).toObject();
            QString itemName = item.value("label").toString();
            QJsonArray computingPowerArray = item.value("computing_power").toArray();

            QCPGraph *graph = customPlot->addGraph();
            graph->setName(itemName);

            int colorIndex = i % lineColors.size();
            graph->setPen(QPen(lineColors[colorIndex]));

            QVector<double> xData, yData;

            for (int j = 0; j < computingPowerArray.size(); ++j)
            {
                QJsonObject point = computingPowerArray.at(j).toObject();
                double x = point.value("time").toString().toDouble();
                double y = point.value("rate").toDouble();

                xData.append(x);
                yData.append(y);
            }

            graph->setData(xData, yData);
            graphs.append(graph);


            QColor brushColor = lineColors[colorIndex];
            brushColor.setAlpha(128);
            graph->setBrush(QBrush(brushColor));

        }

        customPlot->xAxis->setLabel("Time (seconds)");
        customPlot->yAxis->setLabel(yAxisLabel);

        customPlot->legend->setVisible(true);
        customPlot->legend->setBrush(QColor(255, 255, 255, 150));
        customPlot->legend->setBorderPen(Qt::NoPen);

        customPlot->rescaleAxes();
        customPlot->replot();

        customPlot->yAxis->setRange(0, customPlot->yAxis->range().upper * 1.2);

    };
    QJsonArray usersArray = jsonObj.value("users").toArray();
    createGraphs(customPlotUsers, usersArray, "Rate of use of computing power for each user (%)");

    QJsonArray machinesArray = jsonObj.value("machines").toArray();
    createGraphs(customPlotMachines, machinesArray, "Rate of use of computing power for each machine (%)");

    QJsonArray tasksArray = jsonObj.value("tasks").toArray();
    createGraphs(customPlotTasks, tasksArray, "Rate of use of computing power for each task (%)");
}




