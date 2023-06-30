#include "qdebug.h"
#include "qradiobutton.h"
#include "schema.h"
#include <QImage>
#include <QPixmap>
#include <QVBoxLayout>
#include <drawingtable/drawingtable.h>
#include "load/machineload.h"
#include "load/linkload.h"
#include "item/schemaicon.h"
#include "item/link.h"

void printSchema(Schema *schema);

DrawingTable::DrawingTable(QFrame *parent) : DrawingTable(new Schema(), parent)
{}

DrawingTable::DrawingTable(Schema *schema, QWidget *parent) : QWidget{parent}
{
    this->schema = schema;
    this->view   = new View(this);
    this->scene  = new Scene(this);
    this->view->setGScene(scene);

    auto *buttonsRow    = new QWidget(this);
    auto *buttonsLayout = new QHBoxLayout(buttonsRow);
    buttonsLayout->setAlignment(Qt::AlignLeft);

    pcButton = new QRadioButton(buttonsRow);
    pcButton->setIcon(QIcon(QPixmap::fromImage(QImage(":icons/pc.png"))));
    pcButton->setIconSize(QSize(35, 35));
    buttonsLayout->addWidget(pcButton);
    QObject::connect(
        pcButton, &QRadioButton::clicked, this, &DrawingTable::pcButtonClicked);

    schemaButton = new QRadioButton(buttonsRow);
    schemaButton->setIcon(
        QIcon(QPixmap::fromImage(QImage(":icons/cluster.png"))));
    schemaButton->setIconSize(QSize(35, 35));
    buttonsLayout->addWidget(schemaButton);
    QObject::connect(schemaButton,
                     &QRadioButton::clicked,
                     this,
                     &DrawingTable::schemaButtonClicked);

    noneButton = new QRadioButton(buttonsRow);
    noneButton->setIcon(QIcon(QPixmap::fromImage(QImage(":icons/cursor.png"))));
    noneButton->setIconSize(QSize(35, 35));
    buttonsLayout->addWidget(noneButton);
    QObject::connect(noneButton,
                     &QRadioButton::clicked,
                     this,
                     &DrawingTable::noneButtonClicked);

    linkButton = new QRadioButton(buttonsRow);
    // linkButton->setIcon(QIcon(QPixmap::fromImage(QImage(":icons/link.png"))));
    // linkButton->setIconSize(QSize(35, 35));
    buttonsLayout->addWidget(linkButton);
    QObject::connect(linkButton,
                     &QRadioButton::clicked,
                     this,
                     &DrawingTable::linkButtonClicked);

    QObject::connect(
        pcButton, &QRadioButton::clicked, this, &DrawingTable::pcButtonClicked);

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(buttonsRow);
    mainLayout->addWidget(view);
}

MachineIcon *DrawingTable::addMachine()
{
    const unsigned machineId = schema->allocateNewMachine();

    // FOR DEBUG
    printSchema(schema);

    return schema->machines->at(machineId)->icon;
}

SchemaIcon *DrawingTable::addSchema()
{
    const unsigned schemaId = schema->allocateNewSchema();

    // FOR DEBUG
    printSchema(schema);

    return schema->schemas->at(schemaId)->icon;
}

Link *DrawingTable::addLink()
{
    const unsigned linkId = schema->allocateNewLink();

    // FOR DEBUG
    printSchema(schema);

    return schema->links->at(linkId)->line;
}

void DrawingTable::pcButtonClicked()
{
    this->scene->pickOp = PC;
}

void DrawingTable::noneButtonClicked()
{
    this->scene->pickOp = NONE;
}

void DrawingTable::linkButtonClicked()
{
    this->scene->pickOp = LINK;
}

void DrawingTable::schemaButtonClicked()
{
    this->scene->pickOp = SCHEME;
}

void printSchema(Schema *schema)
{
    for (auto machine = schema->machines->begin();
         machine != schema->machines->end();
         machine++) {

        qDebug() << "Machine #" << machine->second->id << ": "
                 << machine->second->icon->getName()->c_str();
    }

    for (auto sch = schema->schemas->begin(); sch != schema->schemas->end();
         sch++) {

        qDebug() << "Schema #" << sch->second->id << ": "
                 << sch->second->icon->getName()->c_str();
    }
}
