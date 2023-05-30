#include "gridscene.h"
#include "clustericon.h"
#include "link.h"
#include "machineicon.h"
#include "qdebug.h"
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <iostream>
#include <string>

/*
 * Create the scene following the QGraphicsScene constructor
 */
GridScene::GridScene(QObject *parent) : QGraphicsScene{parent}
{
    this->items = new QVector<Icon *>();

    this->lBegin = nullptr;
    this->lEnd   = nullptr;
    this->pickOp = NONE;
    this->pIndex = this->cIndex = this->lIndex = 0;

    setSceneRect(0, 0, 2000, 2000);
    drawBackgroundLines();
}

void GridScene::addIcon(Icon *icon, QPointF pos)
{
    icon->setPos(pos);
    icon->setOutputLabel(machineDescriptionLabel);
    this->items->append(icon);
    this->addItem(icon);
}

void GridScene::addLink(Icon *a, Icon *b)
{
    auto newLink = new Link(getNewLinkName().c_str(), a, b);
    this->addItem(newLink);
}

void GridScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    switch (this->pickOp) {
    case NONE: {
        QGraphicsScene::mousePressEvent(event);
        break;
    }
    case PC: {
        auto newMachine = new MachineIcon(getNewMachineName().c_str());
        this->addIcon(newMachine, event->scenePos());
        break;
    }
    case CLUSTER: {
        auto newCluster = new ClusterIcon(getNewClusterName().c_str());
        this->addIcon(newCluster, event->scenePos());
        break;
    }
    case LINK: {
        if (this->lBegin == nullptr) {
            qDebug() << "Primeira máquina\n";
            this->lBegin = whichMachine(event->scenePos());
        }
        else {
            qDebug() << "Segunda máquina\n";

            if (whichMachine(event->scenePos()) == this->lBegin) {
                break;
            }
            this->lEnd = whichMachine(event->scenePos());

            this->addLink(this->lBegin, this->lEnd);

            this->lBegin = nullptr;
            this->lEnd   = nullptr;
        }
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

Icon *GridScene::whichMachine(QPointF pos)
{
    for (auto i = this->items->begin(); i != this->items->end(); i++) {

        qDebug() << pos << " Está em "
                 << (*i)->sceneBoundingRect().contains(pos) << "?\n";
        if ((*i)->sceneBoundingRect().contains(pos)) {
            qDebug() << "Consegui achar " << (*i)->getName()->c_str() << "\n";
            return *i;
        }
    }

    return nullptr;
}

std::string GridScene::getNewMachineName()
{
    std::string newMachineName("Machine");

    newMachineName.append(std::to_string(this->pIndex++));

    return newMachineName;
}

std::string GridScene::getNewClusterName()
{
    std::string newClusterMachine("Cluster");

    newClusterMachine.append(std::to_string(this->cIndex++));

    return newClusterMachine;
}

std::string GridScene::getNewLinkName()
{
    std::string newLinkMachine("Link");

    newLinkMachine.append(std::to_string(this->lIndex++));

    return newLinkMachine;
}
