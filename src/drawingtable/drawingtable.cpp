#include "item/link.h"
#include "item/schemaicon.h"
#include "load/linkload.h"
#include "load/machineload.h"
#include "qdebug.h"
#include "qradiobutton.h"
#include "schema.h"
#include <QImage>
#include <QPixmap>
#include <QVBoxLayout>
#include <drawingtable/drawingtable.h>

void printSchema(Schema *schema);

DrawingTable::DrawingTable(QFrame *parent) : DrawingTable(new Schema(), parent)
{}

DrawingTable::DrawingTable(Schema *schema, QWidget *parent) : QWidget{parent}
{
    this->schema = schema;
    this->view   = new View(this);
    this->scene  = new Scene(this);
    this->view->setGScene(scene);
    this->buttonsRow    = new QWidget(this);
    this->buttonsLayout = new QHBoxLayout(buttonsRow);
    this->buttonsLayout->setAlignment(Qt::AlignLeft);

    setupPcButton();
    setupNoneButton();
    setupLinkButton();
    setupSchemaButton();

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(buttonsRow);
    mainLayout->addWidget(view);
}

///
/// @brief Creates the PC option button and connects it to the scene
///
void DrawingTable::setupPcButton()
{
    pcButton = new QRadioButton(buttonsRow);
    pcButton->setIcon(QIcon(QPixmap::fromImage(QImage(":icons/pc.png"))));
    pcButton->setIconSize(QSize(35, 35));
    buttonsLayout->addWidget(pcButton);
    QObject::connect(
        pcButton, &QRadioButton::clicked, this, &DrawingTable::pcButtonClicked);
}

///
/// @brief Creates the Cursor option button and connects it to the scene
///
void DrawingTable::setupNoneButton()
{
    noneButton = new QRadioButton(buttonsRow);
    noneButton->setIcon(QIcon(QPixmap::fromImage(QImage(":icons/cursor.png"))));
    noneButton->setIconSize(QSize(35, 35));
    buttonsLayout->addWidget(noneButton);
    QObject::connect(noneButton,
                     &QRadioButton::clicked,
                     this,
                     &DrawingTable::noneButtonClicked);
}

///
/// @brief Creates the Schema option button and connects it to the scene
///
void DrawingTable::setupSchemaButton()
{
    schemaButton = new QRadioButton(buttonsRow);
    schemaButton->setIcon(
        QIcon(QPixmap::fromImage(QImage(":icons/cluster.png"))));
    schemaButton->setIconSize(QSize(35, 35));
    buttonsLayout->addWidget(schemaButton);
    QObject::connect(schemaButton,
                     &QRadioButton::clicked,
                     this,
                     &DrawingTable::schemaButtonClicked);
}

///
/// @brief Creates the Link option button and connects it to the scene
///
void DrawingTable::setupLinkButton()
{
    linkButton = new QRadioButton(buttonsRow);
    // linkButton->setIcon(QIcon(QPixmap::fromImage(QImage(":icons/link.png"))));
    // linkButton->setIconSize(QSize(35, 35));
    buttonsLayout->addWidget(linkButton);
    QObject::connect(linkButton,
                     &QRadioButton::clicked,
                     this,
                     &DrawingTable::linkButtonClicked);
}

///
/// @brief  Creates a Machine inside the DrawingTable's Schema
///
/// @return the machine's icon
///
MachineIcon *DrawingTable::addMachine()
{
    const unsigned machineId = schema->allocateNewMachine();

    // FOR DEBUG
    printSchema(schema);

    return schema->machines->at(machineId)->icon;
}

///
/// @brief  Creates a Schema inside the DrawingTable's Schema
///
/// @return the schema's icon
///
SchemaIcon *DrawingTable::addSchema()
{
    const unsigned schemaId = schema->allocateNewSchema();

    // FOR DEBUG
    printSchema(schema);

    return schema->schemas->at(schemaId)->icon;
}

///
/// @brief  Creates a Link inside the DrawingTable's Schema
///
/// @return the link's line
///
Link *DrawingTable::addLink()
{
    const unsigned linkId = schema->allocateNewLink();

    // FOR DEBUG
    printSchema(schema);

    return schema->links->at(linkId)->line;
}

///
/// @brief  set the scene operator to the PC insert mode
///
void DrawingTable::pcButtonClicked()
{
    this->scene->pickOp = PC;
}

///
/// @brief  set the scene operator to the click mode
///
void DrawingTable::noneButtonClicked()
{
    this->scene->pickOp = NONE;
}

///
/// @brief  set the scene operator to the link insert mode
///
void DrawingTable::linkButtonClicked()
{
    this->scene->pickOp = LINK;
}

///
/// @brief  set the scene operator to the schema insert mode
///
void DrawingTable::schemaButtonClicked()
{
    this->scene->pickOp = SCHEMA;
}

///
/// @brief  prints the DrawingTable's Schema and its components
///
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

    for (auto link = schema->links->begin(); link != schema->links->end();
         link++) {

        qDebug() << "Link #" << link->second->id << ": "
                 << link->second->line->getName()->c_str();
    }
}
