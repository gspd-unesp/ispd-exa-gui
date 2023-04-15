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
}
