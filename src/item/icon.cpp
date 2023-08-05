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
#include <QDialog>
#include <QGraphicsView>


Icon::Icon(const char *name, QGraphicsItem *parent)
    : QGraphicsPixmapItem{parent}
{
    this->setFlag(QGraphicsItem::ItemIsMovable);
    this->name       = new std::string(name);
    this->links      = new std::map<unsigned, Link *>();
    this->isSelected = false;
    // this->select = false;

    configuration = IconConfiguration();
}

void Icon::saveConfiguration()
{
    machineIconConfiguration *configDialog = new machineIconConfiguration(this->getName()->c_str());

    configDialog->setLineEdit01Value(this->configuration.labelEdit);
    configDialog->setLineEdit02Value(this->configuration.CompPower_lineEdit);
    configDialog->setLineEdit03Value(this->configuration.cores_lineEdit);
    configDialog->setLineEdit04Value(this->configuration.energyconsumer_lineEdit);
    configDialog->setLineEdit05Value(this->configuration.lineEdit_4);
    configDialog->setLineEdit06Value(this->configuration.loadFactor_lineEdit);
    configDialog->setLineEdit07Value(this->configuration.primarystorage_lineEdit);
    configDialog->setLineEdit08Value(this->configuration.secondaryStorage_lineEdit);

    configDialog->setOwnerComboBoxIndex(this->configuration.ownercomboBoxIndex);
    configDialog->setSchedulingComboBoxIndex(this->configuration.schedulingcomboBoxIndex);
    configDialog->setCheckBoxState(this->configuration.checkBoxState);

    configDialog->show();

    connect(configDialog, &machineIconConfiguration::configurationClicked, this, [this, configDialog]() {
        this->configuration.labelEdit = configDialog->getLineEdit01Value();
        this->configuration.CompPower_lineEdit = configDialog->getLineEdit02Value();
        this->configuration.cores_lineEdit = configDialog->getLineEdit03Value();
        this->configuration.energyconsumer_lineEdit = configDialog->getLineEdit04Value();
        this->configuration.lineEdit_4 = configDialog->getLineEdit05Value();
        this->configuration.loadFactor_lineEdit = configDialog->getLineEdit06Value();
        this->configuration.primarystorage_lineEdit = configDialog->getLineEdit07Value();
        this->configuration.secondaryStorage_lineEdit = configDialog->getLineEdit08Value();

        this->configuration.ownercomboBoxIndex = configDialog->getOwnerComboBoxIndex();
        this->configuration.schedulingcomboBoxIndex = configDialog->getSchedulingComboBoxIndex();
        this->configuration.checkBoxState = configDialog->getCheckBoxState();
    });
}

void Icon::loadConfiguration()
{
    if (!configuration.labelEdit.isEmpty()
        || !configuration.CompPower_lineEdit.isEmpty()
        || !configuration.cores_lineEdit.isEmpty()
        || !configuration.energyconsumer_lineEdit.isEmpty()
        || !configuration.lineEdit_4.isEmpty()
        || !configuration.loadFactor_lineEdit.isEmpty()
        || !configuration.primarystorage_lineEdit.isEmpty()
        || !configuration.secondaryStorage_lineEdit.isEmpty()) {
        machineIconConfiguration *configDialog = new machineIconConfiguration(this->getName()->c_str());

        configDialog->setLineEdit01Value(configuration.labelEdit);
        configDialog->setLineEdit02Value(configuration.CompPower_lineEdit);
        configDialog->setLineEdit03Value(configuration.cores_lineEdit);
        configDialog->setLineEdit04Value(configuration.energyconsumer_lineEdit);
        configDialog->setLineEdit05Value(configuration.lineEdit_4);
        configDialog->setLineEdit06Value(configuration.loadFactor_lineEdit);
        configDialog->setLineEdit07Value(configuration.primarystorage_lineEdit);
        configDialog->setLineEdit08Value(configuration.secondaryStorage_lineEdit);

        configDialog->setOwnerComboBoxIndex(configuration.ownercomboBoxIndex);
        configDialog->setSchedulingComboBoxIndex(configuration.schedulingcomboBoxIndex);
        configDialog->setCheckBoxState(configuration.checkBoxState);

        configDialog->show();
        delete configDialog;
    } else {
    }
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
    // QGraphicsItem* clickedItem01 = itemAt(event->pos().x(), event->pos().y());
    if (event->modifiers() & Qt::ShiftModifier) {
        selection(true);
    } else if (!isSelected){
        for (QGraphicsItem *item : scene()->items()) {
            if (Icon* icon = dynamic_cast<Icon*>(item)) {
                icon->selection(false);
            }
        }
        selection(true);
    }
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

    // Check if Shift key is pressed
    if (event->modifiers() & Qt::ShiftModifier) {
    } else if (!isSelected){
        for (QGraphicsItem *item : scene()->items()) {
            if (Icon* icon = dynamic_cast<Icon*>(item)) {
                icon->selection(false);
            }
        }
    }
    updatePosition();
}

std::string *Icon::getName()
{
    return this->name;
}

void Icon::selection(bool select) {
    if(select && !isSelected) {
        if (!isSelected) {
            isSelected = true;
            auto pixmap = QPixmap::fromImage(QImage(this->iconPathSelected.c_str()))
                              .scaled(iconSelectSize);
            this->setPixmap(pixmap);
        }
    } else if(!select && isSelected) {
        if (isSelected) {
            isSelected = false;
            auto pixmap =
                QPixmap::fromImage(QImage(this->iconPath.c_str())).scaled(iconSize);
            this->setPixmap(pixmap);
        }
    }
}

Icon::~Icon()
{
    delete this->name;
    delete this->links;
}
