#ifndef VIEW_H
#define VIEW_H

#include "drawingtable/scene.h"
#include <QGraphicsView>
#include <QWidget>

class View : public QGraphicsView
{
    Q_OBJECT
    Scene *gScene;

protected:
    void mousePressEvent(QMouseEvent *event);

public:
    View(QWidget *parent = nullptr);
    void setGScene(Scene *scene);
};

#endif
