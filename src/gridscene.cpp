#include "gridscene.h"
#include "clustericon.h"
#include "machineicon.h"
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <iostream>

/*
 * Create the scene following the QGraphicsScene constructor
 */
GridScene::GridScene(QObject *parent) : QGraphicsScene{parent}
{
    this->items = new QVector<Icon *>();

    setSceneRect(0, 0, 2000, 2000);
    drawBackgroundLines();
}

void GridScene::addIcon(Icon *icon, QPointF pos)
{
    icon->setPos(pos);
    icon->setFlag(QGraphicsItem::ItemIsMovable);
    this->items->append(icon);
    this->addItem(icon);
}

void GridScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    switch (this->pickOp) {
    case NONE: {
        QGraphicsScene::mousePressEvent(event);
        break;
    }
    case PC: {
        this->addIcon(new MachineIcon("test"), event->scenePos());
        break;
    }
    case CLUSTER: {
        this->addIcon(new ClusterIcon("test"), event->scenePos());
        break;
    }
    case LINK: {
        break;
    }
    }
}

void GridScene::drawBackgroundLines()
{
    auto rect = sceneRect();

    for (qreal i = 40; i <= rect.height(); i += 40) {
        auto line = new QLine(0, i, rect.width(), i);
        addLine(*line);
    }

    for (qreal i = 40; i <= rect.width(); i += 40) {
        auto line = new QLine(i, 0, i, rect.height());
        addLine(*line);
    }
}
