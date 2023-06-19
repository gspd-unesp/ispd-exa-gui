#include "drawingtable/scene.h"
#include "item/clustericon.h"
#include "item/link.h"
#include "item/machineicon.h"
#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <iostream>
#include <string>

#include <QGraphicsScene>
#include <QKeyEvent>

/*
 * Create the scene following the QGraphicsScene constructor
 */
Scene::Scene(QObject *parent) : QGraphicsScene{parent}
{
    this->items = new QVector<Icon *>();
    this->lBegin = nullptr;
    this->lEnd   = nullptr;
    this->pickOp = NONE;
    this->pIndex = this->cIndex = this->lIndex = 0;

    setSceneRect(0, 0, 2000, 2000);
    drawBackgroundLines();
}

void Scene::addIcon(Icon *icon, QPointF pos)
{
    icon->setPos(pos);
    icon->setOutputLabel(machineDescriptionLabel);
    this->items->append(icon);
    this->addItem(icon);
    icon->isSelected;
}

void Scene::addLink(Icon *a, Icon *b)
{
    auto newLink = new Link(getNewLinkName().c_str(), a, b);
    this->addItem(newLink);
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete) {
        QList<QGraphicsItem*> itemList = QGraphicsScene::items();
        QList<Icon*> itemsToRemove;
        QList<Link*> linksToRemove;

        bool linkSelected = false;

        for (QGraphicsItem* item : itemList) {
            Icon* icon = dynamic_cast<Icon*>(item);
            Link* linkitem = dynamic_cast<Link*>(item);

            if (icon && icon->isSelected) {
                qDebug() << "Entrou if";
                itemsToRemove.append(icon);

                for (Link* link : *icon->links) {
                    linksToRemove.append(link);

                    // Remove o link do outro ícone
                    Icon* otherIcon = (link->begin == icon) ? link->end : link->begin;
                    otherIcon->links->removeOne(link);
                }

                // Limpa a lista de links do ícone
                icon->links->clear();
            } else if (linkitem && (linkitem->begin->isSelected || linkitem->end->isSelected)) {
                qDebug() << "Entrou no else if";
                linksToRemove.append(linkitem);
                linkSelected = true;
            }
        }

        if (linkSelected) {
            for (Link* link : linksToRemove) {
                removeItem(link);
                delete link;
            }
        }
        else {
            for (Icon* icon : itemsToRemove) {
                // Remove os links associados ao ícone da cena e os deleta
                for (Link* link : *icon->links) {
                    removeItem(link);
                    delete link;
                }

                removeItem(icon);
                items->removeAll(icon);
                delete icon;
            }

            // Remove os links da cena
            for (Link* link : linksToRemove) {
                removeItem(link);
                delete link;
            }
        }
    }
    QGraphicsScene::keyPressEvent(event);
}




void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
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
        else if  (this->lEnd == nullptr){
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
        auto line = new QLine(0, i, rect.width(), i);
        addLine(*line, pen);
    }

    for (qreal i = 40; i <= rect.width(); i += 40) {
        auto line = new QLine(i, 0, i, rect.height());
        addLine(*line, pen);
    }
}

Icon *Scene::whichMachine(QPointF pos)
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

std::string Scene::getNewMachineName()
{
    std::string newMachineName("Machine");

    newMachineName.append(std::to_string(this->pIndex++));

    return newMachineName;
}

std::string Scene::getNewClusterName()
{
    std::string newClusterMachine("Cluster");

    newClusterMachine.append(std::to_string(this->cIndex++));

    return newClusterMachine;
}

std::string Scene::getNewLinkName()
{
    std::string newLinkMachine("Link");

    newLinkMachine.append(std::to_string(this->lIndex++));

    return newLinkMachine;
}
