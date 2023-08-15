#include "window/drawingtable/scene.h"
#include "components/cloner/machinecloner.h"
#include "components/link.h"
#include "components/schema.h"
#include "components/switch.h"
#include "icon/linkicon.h"
#include "icon/pixmapicon.h"
#include "qnamespace.h"
#include "window/drawingtable/drawingtable.h"
#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPoint>
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <tuple>

///
/// Create the scene following the QGraphicsScene constructor
///
Scene::Scene(DrawingTable *parent) : QGraphicsScene{parent}
{
    this->table  = parent;
    this->schema = this->table->schema;
    this->lBegin = nullptr;
    this->lEnd   = nullptr;
    this->pickOp = NONE;

    setSceneRect(0, 0, 2000, 2000);
    drawBackgroundLines();
}

QPointF Scene::getScenePosition()
{
    QGraphicsView *view           = this->views().first();
    QPoint         globalMousePos = QCursor::pos();
    QPointF        sceneMousePos =
        view->mapToScene(view->mapFromGlobal(globalMousePos));
    return sceneMousePos;
}

///
/// @brief Add an Icon to the position specified.
///
/// @params icon an icon (Machine, Schema...)
/// @params pos  the position to set the icon
///
void Scene::addIcon(PixmapIcon *icon, QPointF pos)
{
    icon->setPos(pos);
    this->addItem(icon);
}

///
/// @brief Add an Link to the position specified.
///
/// @params link an Link
/// @params a    the Item that the Link comes from
/// @params b    the Item that the Link goes to
///
void Scene::addLink(Link *link)
{
    link->addLine();

    this->addItem(link->icon.get());
}

Schema *findScheme(Schema *schema)
{
    for (auto &it : schema->schemas) {
        if (it.second->getIcon()->isChosen()) {
            return it.second.release();
        }
    }
    return nullptr;
}

Machine *findMachine(Schema *schema)
{
    for (auto &it : schema->machines) {
        if (it.second->getIcon()->isChosen()) {
            return it.second.get();
        }
    }
    return nullptr;
}

void printThisSchema(Schema *schema)
{
    qDebug() << "From Schema: " << schema->getConf()->getName();
    for (auto &machine : schema->machines) {
        qDebug() << "Machine[" << machine.second->conf->getId()
                 << "] = " << machine.second->conf->getName();
    }
}

///
/// @brief Handles a keyboard keypress.
///
/// @params event a keyboard event
///
void Scene::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Delete:
        this->deleteItems();
        break;
    case Qt::Key_C:
        qDebug() << "Aconteceu algo?";
        this->mCloner = new MachineCloner(findMachine(this->schema), nullptr);
        break;
    case Qt::Key_V:
        auto clone = this->mCloner->clone(this->schema);
        this->addIcon(clone->getIcon(), getScenePosition());
        this->schema->machines[clone->conf->getId()] = std::move(clone);
        printThisSchema(this->schema);
        break;
    }

    QGraphicsScene::keyPressEvent(event);
}

void Scene::deleteItems()
{
    qDebug() << "Test of deleteItems.";

    auto eraseCondition = [](auto const &it) {
        qDebug() << "BEGIN TO DELETE " << it.second->getConf()->getName();
        return it.second->getIcon()->isChosen();
    };

    erase_if(this->schema->machines, eraseCondition);
    erase_if(this->schema->switches, eraseCondition);
    erase_if(this->schema->schemas, eraseCondition);
    erase_if(this->schema->links, eraseCondition);
}

QRectF getOwnItemsSceneBoundingRect(Schema *schema)
{
    QRectF boundingRect;

    for (auto &[id, machine] : schema->machines)
        boundingRect |= machine->getIcon()->sceneBoundingRect();
    for (auto &[id, schema] : schema->schemas)
        boundingRect |= schema->getIcon()->sceneBoundingRect();
    for (auto &[id, nSwitch] : schema->switches)
        boundingRect |= nSwitch->getIcon()->sceneBoundingRect();
    for (auto &[id, link] : schema->links)
        boundingRect |= link->getIcon()->sceneBoundingRect();

    return boundingRect;
}

///
/// @brief Handles the mouse press, adapting the behavior based on the actual
///        state.
///
/// @params event a mouse press event
///
void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    switch (this->pickOp) {
    case NONE: {
        if (getOwnItemsSceneBoundingRect(this->schema)
                .contains(event->scenePos())) {
            QGraphicsScene::mousePressEvent(event);
        }
        else {
            selectionArea(event);
        }
        return;
    }
    case PC: {
        auto newMachine = this->table->addMachine();

        this->addIcon(newMachine, event->scenePos());

        break;
    }
    case SCHEMA: {
        auto newSchema = this->table->addSchema();
        this->addIcon(newSchema, event->scenePos());
        if (newSchema->getOwner()) {
            qDebug() << "Owner of schema exists";
            break;
        }
        qDebug() << "Owner of schema exists";
        break;
    }
    case LINK: {
        auto *connection = whichConnection(event->scenePos());

        if (!connection) {
            return;
        }

        if (this->lBegin == nullptr) {
            qDebug() << "Primeira máquina\n";
            this->lBegin = connection;
        }
        else if (this->lEnd == nullptr) {

            if (whichConnection(event->scenePos()) == this->lBegin) {
                break;
            }
            this->lEnd = connection;

            Link *newLink =
                this->table->addLink(LinkConnections{this->lBegin, this->lEnd});
            qDebug() << "Antes de enfia link na scene.";
            this->addLink(newLink);

            this->lBegin = nullptr;
            this->lEnd   = nullptr;
        }
        break;
    }
    case SWITCH: {
    }
        auto newSwitch = this->table->addSwitch();

        this->addIcon(newSwitch, event->scenePos());

        break;
    }
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->startSelection != QPointF()) {
        QRectF selectionAreaRect =
            QRectF(this->startSelection, event->scenePos()).normalized();
        this->selectionRect->setRect(selectionAreaRect);
    }
    QGraphicsScene::mouseMoveEvent(event);
}

template <class T>
void toggleSelectionIfInside(QRectF area, Item<T> *item)
{
    auto icon = item->getIcon();
    if (area.contains(item->getIcon()->sceneBoundingRect()) &&
        !icon->isChosen()) {
        item->getIcon()->toggleChoosen();
    }
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton &&
        this->startSelection != QPointF()) {
        // Calculate the selection area rectangle
        QRectF selectionAreaRect =
            QRectF(this->startSelection, event->scenePos()).normalized();

        // Deselect all icons outside the selection area
        for (auto &[id, machine] : this->schema->machines) {
            toggleSelectionIfInside(selectionAreaRect, machine.get());
        }
        for (auto &[id, schema] : this->schema->schemas) {
            toggleSelectionIfInside(selectionAreaRect, schema.get());
        }
        for (auto &[id, nSwitch] : this->schema->switches) {
            toggleSelectionIfInside(selectionAreaRect, nSwitch.get());
        }
        for (auto &[id, link] : this->schema->links) {
            toggleSelectionIfInside(selectionAreaRect, link.get());
        }

        // Reset the initial position for area selection
        this->startSelection = QPointF();
        delete this->selectionRect;
        this->selectionRect = nullptr;
    }

    QGraphicsScene::mouseReleaseEvent(event);
}

void Scene::selectionArea(QGraphicsSceneMouseEvent *event)
{
    /* Connection *clickedIcon = whichConnection(event->scenePos()); */
    /* if (!clickedIcon && !static_cast<Icon *>(clickedIcon)) { */
    if (event->button() == Qt::LeftButton) {
        this->startSelection = event->scenePos();
        this->selectionRect  = new QGraphicsRectItem();
        this->selectionRect->setPen(
            QPen(Qt::blue, 1, Qt::SolidLine)); // Change color and pen style
        this->selectionRect->setBrush(QBrush(QColor(100, 100, 255, 40)));
        this->selectionRect->setRect(
            QRectF(this->startSelection, event->scenePos()).normalized());
        this->addItem(this->selectionRect); // Add the selection rectangle
                                            // to the scene
    }
    /* } */
}

///
/// @brief Draw lines at the background of the scene.
///
void Scene::drawBackgroundLines()
{
    auto rect = sceneRect();
    QPen pen; // creates a default pen

    pen.setStyle(Qt::SolidLine);
    pen.setWidth(1);
    pen.setColor(QColor(211, 211, 211, 255));
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);

    for (qreal i = 40; i <= rect.height(); i += 40) {
        auto line = new QGraphicsLineItem(0, i, rect.width(), i);
        line->setPen(pen);
        line->setZValue(-2);
        addItem(line);
    }

    for (qreal i = 40; i <= rect.width(); i += 40) {
        auto line = new QGraphicsLineItem(i, 0, i, rect.height());
        line->setPen(pen);
        line->setZValue(-2);
        addItem(line);
    }
}

///
/// @brief  Finds the machine icon located at the specified position within
///         the scene.
///
/// @param  pos The position in the scene to check for a machine icon.
/// @return a pointer to the machine icon if found, or nullptr if not found.
///
Connection *Scene::whichConnection(QPointF pos)
{
    for (auto &[machineid, machine] : this->schema->machines) {
        if (machine->icon->sceneBoundingRect().contains(pos)) {
            return machine.get();
        }
    }

    for (auto &[schemaid, schema] : this->schema->schemas) {
        if (schema->icon->sceneBoundingRect().contains(pos)) {
            return schema.get();
        }
    }

    for (auto &[switchid, nSwitch] : this->schema->switches) {
        if (nSwitch->getIcon()->sceneBoundingRect().contains(pos)) {
            return nSwitch.get();
        }
    }
    return nullptr;
}
