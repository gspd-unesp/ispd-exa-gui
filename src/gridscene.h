#ifndef GRIDSCENE_H
#define GRIDSCENE_H

#include "qvector.h"
#include "src/icon.h"
#include <QGraphicsScene>
#include <QWidget>

class GridScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit GridScene(QObject *parent = nullptr);
    QVector<Icon *> *items;
    void             addIcon(Icon *icon);
    void             drawBackgroundLines();

signals:
    void clicked(QPointF position);
};

#endif // GRIDSCENE_H
