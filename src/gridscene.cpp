#include "gridscene.h"
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <iostream>

/*
 * Create the scene following the QGraphicsScene constructor
 */
GridScene::GridScene(QObject *parent) : QGraphicsScene{parent}
{
    this->items = new QVector<Icon*>();

    setSceneRect(0, 0, 2000, 2000);
    drawBackgroundLines();

}

void GridScene::addIcon(Icon *icon)
{
    icon->setFlag(QGraphicsItem::ItemIsMovable);
    this->items->append(icon);
    this->addItem(icon);
}

void GridScene::drawBackgroundLines() {
    auto rect = sceneRect();

    for (qreal i = 40; i <= rect.height(); i+= 40) {
        auto line = new QLine(0, i, rect.width(), i);
        addLine(*line);
    }

    for (qreal i = 40; i <= rect.width(); i+= 40) {
        auto line = new QLine(i, 0, i, rect.height());
        addLine(*line);
    }

}
