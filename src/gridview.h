#ifndef GRIDVIEW_H
#define GRIDVIEW_H

#include "gridscene.h"
#include <QGraphicsView>
#include <QWidget>

class GridView : public QGraphicsView
{
    Q_OBJECT
    GridScene *gScene;

protected:
    void mousePressEvent(QMouseEvent *event);

public:
    GridView(QWidget *parent = nullptr);
    void setGScene(GridScene *scene);
};

#endif // GRIDVIEW_H
