#include "window/drawingtable/scene.h"
#include "components/cloner/connectablecloner.h"
#include "components/cloner/machinecloner.h"
#include "components/conf/machineconfiguration.h"
#include "components/link.h"
#include "components/schema.h"
#include "components/switch.h"
#include "icon/linkicon.h"
#include "icon/pixmapicon.h"
#include "qgraphicsitem.h"
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
Scene::Scene(DrawingTable *parent)
    : QGraphicsScene{parent}, pickOp(NONE), table(parent)
{
    this->schema = this->table->schema;
    this->lBegin = nullptr;
    this->lEnd   = nullptr;
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
    link->getIcon()->draw();

    this->addItem(link->icon.get());
}

void printThisSchema(Schema *schema)
{
    qDebug() << "From Schema: " << schema->getConf()->getName().c_str();
    for (auto &connectable : schema->connectables) {
        qDebug() << "Machine[" << connectable.second->getConf()->getId()
                 << "] = " << connectable.second->getConf()->getName().c_str();
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
        this->sceneCloner =
            whichConnectable(getScenePosition())->cloner(nullptr);
        break;
    case Qt::Key_V:
        qDebug() << "Vamos ver se está clonando.";
        auto newConnectable = this->sceneCloner->clone(this->schema);
        this->addIcon(newConnectable->getIcon(), this->getScenePosition());
        this->schema->connectables[newConnectable->getConf()->getId()] =
            std::move(newConnectable);

        break;
    }

    QGraphicsScene::keyPressEvent(event);
}

void Scene::deleteItems()
{
    auto eraseCondition = [](auto const &it) {
        return it.second->getIcon()->isChosen();
    };

    erase_if(this->schema->connectables, eraseCondition);
    erase_if(this->schema->links, eraseCondition);
}

QRectF getOwnItemsSceneBoundingRect(Schema *schema)
{
    QRectF boundingRect;

    for (auto &[id, machine] : schema->connectables)
        boundingRect |= machine->getIcon()->sceneBoundingRect();
    for (auto &[id, link] : schema->links)
        boundingRect |=
            static_cast<LinkIcon *>(link->getIcon())->sceneBoundingRect();

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
            break;
        }
        break;
    }
    case LINK: {
        auto *connection = whichConnectable(event->scenePos());

        if (!connection) {
            return;
        }

        if (this->lBegin == nullptr) {
            this->lBegin = connection;
        }
        else if (this->lEnd == nullptr) {

            if (whichConnectable(event->scenePos()) == this->lBegin) {
                break;
            }
            this->lEnd = connection;

            Link *newLink =
                this->table->addLink(LinkConnections{this->lBegin, this->lEnd});
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

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton &&
        this->startSelection != QPointF()) {
        // Calculate the selection area rectangle
        QRectF selectionAreaRect =
            QRectF(this->startSelection, event->scenePos()).normalized();

        // Deselect all icons outside the selection area
        for (auto &[id, machine] : this->schema->connectables) {
            machine->getIcon()->toggleChosenIfInside(selectionAreaRect);
        }
        for (auto &[id, link] : this->schema->links) {
            link->getIcon()->toggleChosenIfInside(selectionAreaRect);
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
Connectable *Scene::whichConnectable(QPointF pos)
{
    for (auto &[connectableId, connectable] : this->schema->connectables) {
        if (connectable->getIcon()->sceneBoundingRect().contains(pos)) {
            return connectable.get();
        }
    }

    return nullptr;
}
