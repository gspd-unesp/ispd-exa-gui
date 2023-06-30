#include "drawingtable/scene.h"
#include "item/schemaicon.h"
#include "item/link.h"
#include "item/machineicon.h"
#include "drawingtable/drawingtable.h"
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
    this->icons  = new QVector<Icon *>();
    this->links  = new QVector<Link *>();
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
    this->addItem(icon);
    this->icons->append(icon);
}

void Scene::addLink(Link *link, Icon *a, Icon *b)
{
    qDebug() << "Antes de desenharr.";
    link->draw(a, b);
    qDebug() << "Antes de adicionar na scene.";
    this->addItem(link);
    qDebug() << "Depois de adicionar a scene";
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete) {
        QList<Icon *> iconsToRemove;
        QList<Link *> linksToRemove;

        for (auto *icon : *icons) {
            if (icon->isSelected) {
                qDebug() << "Deletando ícone " << icon->getName()->c_str()
                         << "\n";

                iconsToRemove.append(icon);

                for (auto *link : *icon->links) {
                    qDebug() << "Deletando link " << link->getName()->c_str()
                             << "\n";
                    linksToRemove.append(link);

                    auto *otherIcon =
                        (link->begin == icon) ? link->end : link->begin;
                    otherIcon->links->removeOne(link);
                }
                icon->links->clear();
            }
        }
        for (Icon *icon : iconsToRemove) {
            // Remove os links associados ao ícone da cena e os deleta
            for (Link *link : *icon->links) {
                removeItem(link);
                delete link;
            }

            removeItem(icon);
            icons->removeAll(icon);
            delete icon;
        }

        // Remove os links da cena
        for (Link *link : linksToRemove) {
            removeItem(link);
            delete link;
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
        // auto newMachine = new MachineIcon(getNewMachineName().c_str());
        auto newMachine = ((DrawingTable *) this->parent())->addMachine();
        this->addIcon(newMachine, event->scenePos());
        break;
    }
    case SCHEMA: {
        auto newSchema = ((DrawingTable *) this->parent())->addSchema();
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
            qDebug() << "Primeira máquina\n";
            this->lBegin = machine;
        }
        else if (this->lEnd == nullptr) {
            qDebug() << "Segunda máquina\n";

            if (whichMachine(event->scenePos()) == this->lBegin) {
                break;
            }
            this->lEnd = machine;

            auto *newLink = ((DrawingTable *) this->parent())->addLink();
            qDebug() << "Antes de enfia link na scene.";
            this->addLink(newLink, this->lBegin, this->lEnd);

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
    for (auto i = this->icons->begin(); i != this->icons->end(); i++) {

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
