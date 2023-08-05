#include "drawingtable/scene.h"
#include "drawingtable/drawingtable.h"
#include "item/link.h"
#include "item/machineicon.h"
#include "item/schemaicon.h"
#include "qgraphicsitem.h"
#include "window/users.h"
#include "window/machineconfiguration.h"
#include "schema.h"
#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <iostream>
#include <string>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>

///
/// Create the scene following the QGraphicsScene constructor
///
Scene::Scene(QObject *parent) : QGraphicsScene{parent}
{
    this->icons  = new QVector<Icon *>();
    this->links  = new QVector<Link *>();
    this->lBegin = nullptr;
    this->lEnd   = nullptr;
    this->pickOp = NONE;

    setSceneRect(0, 0, 2000, 2000);
    drawBackgroundLines();
}

///
/// @brief Add an Icon to the position specified.
///
/// @params icon an icon (Machine, Schema...)
/// @params pos  the position to set the icon
///
void Scene::addIcon(Icon *icon, QPointF pos)
{
    icon->setPos(pos);
    icon->setOutputLabel(machineDescriptionLabel);
    this->addItem(icon);
    this->icons->append(icon);
}

///
/// @brief Add an Link to the position specified.
///
/// @params link an Link
/// @params a    the icon that the Link comes from
/// @params b    the icon that the Link goes to
///
void Scene::addLink(Link *link, Icon *a, Icon *b)
{
    link->draw(a, b);
    this->addItem(link);
}

///
/// @brief Handles a keyboard keypress.
///
/// @params event a keyboard event
///
void Scene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete) {
        std::map<unsigned, Icon *> iconsToRemove;
        std::map<unsigned, Link *> linksToRemove;

        for (auto *icon : *icons) {
            if (icon->isSelected) {
                iconsToRemove.insert(std::pair(icon->id, icon));

                for (auto link : *icon->links) {
                    linksToRemove.insert(link);

                    auto *otherIcon = (link.second->begin == icon)
                                          ? link.second->end
                                          : link.second->begin;
                    otherIcon->links->erase(link.first);
                }
                icon->links->clear();
            }
        }

        for (auto icon : iconsToRemove) {
            if (dynamic_cast<MachineIcon *>(icon.second) != nullptr) {
                this->removeMachine((MachineIcon *)icon.second);
            }
        }

        for (auto link : linksToRemove) {
            this->removeLink(link.second);
        }
    }

    QGraphicsScene::keyPressEvent(event);
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
        selectionArea(event);
        QGraphicsScene::mousePressEvent(event);
        break;
    }
    case PC: {
        // auto newMachine = new MachineIcon(getNewMachineName().c_str());
        auto newMachine = ((DrawingTable *)this->parent())->addMachine();
        this->addIcon(newMachine, event->scenePos());
        break;
    }
    case SCHEMA: {
        auto newSchema = ((DrawingTable *)this->parent())->addSchema();
        this->addIcon(newSchema, event->scenePos());
        if (newSchema->owner) {
            qDebug() << "Owner of schema exists";
            break;
        }
        qDebug() << "Owner of schema exists";
        break;
    }
    case LINK: {
        auto *machine = whichMachine(event->scenePos());

        if (!machine) {
            return;
        }

        if (this->lBegin == nullptr) {
            this->lBegin = machine;
        }
        else if (this->lEnd == nullptr) {

            if (whichMachine(event->scenePos()) == this->lBegin) {
                break;
            }
            this->lEnd = machine;

            auto *newLink = ((DrawingTable *)this->parent())->addLink();
            this->addLink(newLink, this->lBegin, this->lEnd);

            this->lBegin = nullptr;
            this->lEnd   = nullptr;
        }
        break;
    }
    }
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (this->startSelection != QPointF()) {
        QRectF selectionAreaRect = QRectF(this->startSelection, event->scenePos()).normalized();
        this->selectionRect->setRect(selectionAreaRect);
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && this->startSelection != QPointF()) {
        // Calculate the selection area rectangle
        QRectF selectionAreaRect = QRectF(this->startSelection, event->scenePos()).normalized();

        // Deselect all icons outside the selection area
        for (auto item : this->items()) {
            if (Icon *icon = dynamic_cast<Icon *>(item)) {
                if (selectionAreaRect.contains(icon->sceneBoundingRect())) {
                    icon->selection(true);
                } else {
                    icon->selection(false);
                }
            }
        }
        // Reset the initial position for area selection
        this->startSelection = QPointF();
        this->removeItem(this->selectionRect); // Remove the selection rectangle from the scene
        delete this->selectionRect;
        this->selectionRect = nullptr;
    }

    QGraphicsScene::mouseReleaseEvent(event);
}

void Scene::selectionArea(QGraphicsSceneMouseEvent *event) {
    Icon *clickedIcon = whichMachine(event->scenePos());
    if (!clickedIcon && !dynamic_cast<MachineIcon*>(clickedIcon)) {
        if (event->button() == Qt::LeftButton) {
            this->startSelection = event->scenePos();
            this->selectionRect = new QGraphicsRectItem();
            this->selectionRect->setPen(QPen(Qt::blue, 1, Qt::SolidLine)); // Change color and pen style
            this->selectionRect->setBrush(QBrush(QColor(100, 100, 255, 40)));
            this->selectionRect->setRect(QRectF(this->startSelection, event->scenePos()).normalized());
            this->addItem(this->selectionRect); // Add the selection rectangle to the scene
        }
    }
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
Icon *Scene::whichMachine(QPointF pos)
{
    for (auto i = this->icons->begin(); i != this->icons->end(); i++) {
        if ((*i)->sceneBoundingRect().contains(pos)) {
            return *i;
        }
    }

    return nullptr;
}

void Scene::removeMachine(MachineIcon *icon)
{
    unsigned id         = icon->id;
    Schema  *sceneOwner = ((DrawingTable *)this->parent())->schema;

    this->icons->removeOne(icon);
    sceneOwner->deleteMachine(id);

    removeItem(icon);

    delete (icon);
}

void Scene::removeLink(Link *link)
{
    unsigned id         = link->id;
    Schema  *sceneOwner = ((DrawingTable *)this->parent())->schema;

    this->links->removeOne(link);

    sceneOwner->deleteLink(id);

    removeItem(link);
}

void Scene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Icon *clickedIcon = whichMachine(event->scenePos());
    if (clickedIcon && dynamic_cast<MachineIcon*>(clickedIcon)) {
        clickedIcon->loadConfiguration();
        clickedIcon->saveConfiguration();
    }
    QGraphicsScene::mouseDoubleClickEvent(event);
}
