#ifndef GRIDSCENE_H
#define GRIDSCENE_H

#include <QGraphicsScene>
#include <QWidget>

class GridScene : public QGraphicsScene
{
public:
    explicit GridScene(QObject *parent = nullptr);
};

#endif // GRIDSCENE_H
