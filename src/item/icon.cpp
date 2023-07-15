#include "item/icon.h"
#include "item/link.h"
#include "utils/iconSize.h"
#include <QDebug>
#include <QGraphicsScene>
#include <map>
#include <QKeyEvent>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <iostream>
#include <string>

Icon::Icon(const char *name, QGraphicsItem *parent)
    : QGraphicsPixmapItem{parent}
{
    this->setFlag(QGraphicsItem::ItemIsMovable);
    this->name       = new std::string(name);
    this->links      = new std::map<unsigned, Link *>();
    this->isSelected = false;
}

/*
 * @brief Update dinamically the Icon's links position when moving it.
 *
 * @see   Scene
 * @param event the mouse event from the icon's scene
 */
void Icon::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsPixmapItem::mouseMoveEvent(event);
    updatePosition();
}

/*
 * @brief Helper function to update Icon's position and its Links
 */
void Icon::updatePosition()
{
    QString pos_string =
        QString("Position: %1, %2").arg(this->pos().x()).arg(this->pos().y());

    for (auto link = links->begin(); link != links->end(); link++) {
        (*link).second->updatePositions();
    }
}

/*
 * Configure the event of clicking the item to print the position of it and
 * select it.
 */
void Icon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "(" << this->pos().x() << " , " << this->pos().y() << ")"
             << "\n";


    QGraphicsPixmapItem::mousePressEvent(event);

    // Check if Shift key is pressed
    if (event->modifiers() & Qt::ShiftModifier) {
    } else {
        for (QGraphicsItem *item : scene()->items()) {
            qDebug() << "Shift está selecionado";
                if (Icon* icon = dynamic_cast<Icon*>(item)) {
                icon->deselect();
            }
        }
    }
    qDebug() << "Terminous de clicar";

    select();
}

void Icon::setOutputLabel(QLabel *label)
{
    this->outputLabel = label;
}

/*
 * Configure the event of releasing the mouse to check if the item is
 * inside its scene, if it's not, move it inside.
 */
void Icon::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Aqui?";
    QGraphicsItem::mouseReleaseEvent(event);
    auto pos    = this->pos();
    auto height = this->scene()->sceneRect().height();
    auto width  = this->scene()->sceneRect().width();

    if (pos.x() <= 0) {
        this->moveBy(-pos.x(), 0);
    }

    if (pos.y() <= 0) {
        this->moveBy(0, -pos.y());
    }

    if (pos.x() > width) {
        this->moveBy(-(pos.x() - width), 0);
    }

    if (pos.y() > height) {
        this->moveBy(0, -(pos.y() - height));
    }

    qDebug() << "Ou aqui?";
    updatePosition();
    qDebug() << "Ou  até aqui?";
}

std::string *Icon::getName()
{
    return this->name;
}

void Icon::select()
{
    if (!isSelected) {
        isSelected = true;
        auto pixmap = QPixmap::fromImage(QImage(this->iconPathSelected.c_str()))
                          .scaled(iconSelectSize);
        this->setPixmap(pixmap);
    }
}

void Icon::deselect()
{
    if (isSelected) {
        isSelected = false;
        auto pixmap =
            QPixmap::fromImage(QImage(this->iconPath.c_str())).scaled(iconSize);
        this->setPixmap(pixmap);
    }
}

Icon::~Icon()
{
    delete this->name;
    delete this->links;
}
