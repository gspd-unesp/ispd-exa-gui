#include "window/drawingtable/drawingtable.h"
#include "components/link.h"
#include "components/machine.h"
#include "components/schema.h"
#include "icon/linkicon.h"
#include "icon/schemaicon.h"
#include "qdebug.h"
#include "qpushbutton.h"
#include "qradiobutton.h"
#include "utils/iconSize.h"
#include "window/users.h"
#include <QImage>
#include <QPixmap>
#include <QVBoxLayout>

void printSchema(Schema *schema);

DrawingTable::DrawingTable(QFrame *parent)
    : DrawingTable(new Schema(""), parent)
{
    QPixmap image(":/icons/perfil.png");
    QSize   imageSize(30, 30);
    QPixmap resizedImage =
        image.scaled(imageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    openUserWindow = new QPushButton(this);
    openUserWindow->setIcon(QIcon(resizedImage));
    openUserWindow->setIconSize(image.size());
    openUserWindow->setFixedSize(40, 40);

    //----------------------------------------------------------------------------------------

    QPixmap image_2(":/icons/engine.png");
    QSize   imageSize_2(30, 30);
    QPixmap resizedImage_2 = image_2.scaled(
        imageSize_2, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    openSimulationWindow = new QPushButton("Simulate", this);
    openSimulationWindow->setIcon(QIcon(resizedImage_2));
    openSimulationWindow->setIconSize(imageSize_2);

    openSimulationWindow->setFixedSize(100, 40);

    //----------------------------------------------------------------------------------------

    buttonsLayout->addWidget(openUserWindow, 0, Qt::AlignRight);
    buttonsLayout->addWidget(openSimulationWindow, 0, Qt::AlignRight);

    connect(openUserWindow,
            &QPushButton::clicked,
            this,
            &DrawingTable::openUserWindowClicked);
    connect(openSimulationWindow,
            &QPushButton::clicked,
            this,
            &DrawingTable::openSimulationWindowClicked);
}

DrawingTable::DrawingTable(Schema *schema, QWidget *parent) : QWidget{parent}
{
    this->schema = schema;
    this->view   = new View(this);
    this->scene  = new Scene(this);
    this->view->setGScene(scene);
    this->buttonsRow    = new QWidget(this);
    this->buttonsLayout = new QHBoxLayout(buttonsRow);
    this->buttonsLayout->setAlignment(Qt::AlignLeft);

    this->setupPcButton();
    this->setupNoneButton();
    this->setupLinkButton();
    this->setupSchemaButton();

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(buttonsRow);
    mainLayout->addWidget(view);
}

void DrawingTable::receiveUserWindowData(const QList<QString> &list1Data, const QList<double> &list2Data)
{
    this->list1Data = list1Data;
    this->list2Data = list2Data;
}

///
/// @brief Creates the PC option button and connects it to the scene
///
void DrawingTable::setupPcButton()
{
    this->pcButton = new QRadioButton(this->buttonsRow);
    this->pcButton->setIcon(QIcon(QPixmap::fromImage(QImage(":icons/pc.png"))));
    this->pcButton->setIconSize(buttonSize);
    this->buttonsLayout->addWidget(pcButton);
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
    noneButton->setIconSize(buttonSize);
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
    schemaButton->setIconSize(buttonSize);
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
    const QIcon linkIcon(QPixmap::fromImage(QImage(":icons/connection.png")));

    linkButton = new QRadioButton(buttonsRow);
    linkButton->setIcon(linkIcon);
    linkButton->setIconSize(buttonSize);
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

    return schema->machines.at(machineId)->getIcon();
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

    return schema->schemas.at(schemaId)->getIcon();
}

///
/// @brief  Creates a Link inside the DrawingTable's Schema
///
/// @return the link's line
///
Link *DrawingTable::addLink(LinkConnections connections)
{
    const unsigned linkId = schema->allocateNewLink(connections);

    // FOR DEBUG
    printSchema(schema);

    return schema->links.at(linkId).get();
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
    for (auto machine = schema->machines.begin();
         machine != schema->machines.end();
         machine++) {

        qDebug() << "Machine #" << machine->second->id << ": "
                 << machine->second->icon->getName()->c_str();
    }

    for (auto sch = schema->schemas.begin(); sch != schema->schemas.end();
         sch++) {

        qDebug() << "Schema #" << sch->second->id << ": "
                 << sch->second->icon->getName()->c_str();
    }

    for (auto link = schema->links.begin(); link != schema->links.end();
         link++) {

        qDebug() << "Link #" << link->second->id << ": "
                 << link->second->icon->getName()->c_str();
    }
}
void DrawingTable::openUserWindowClicked()
{
    this->userWindow = new UserWindow(nullptr, this, list1Data, list2Data); // Pass the lists to UserWindow constructor

    userWindow->show();
}

void DrawingTable::openSimulationWindowClicked()
{
    this->simulationWindow = new Simulation();
    simulationWindow->show();
}
