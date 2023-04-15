#include "gridscene.h"
#include <iostream>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>

GridScene::GridScene(QObject* parent)
  : QGraphicsScene{ parent }
{
}
