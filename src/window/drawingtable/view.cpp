#include "window/drawingtable/view.h"
#include "window/drawingtable/scene.h"
#include <QDebug>
#include <QGraphicsView>
#include <QMouseEvent>
#include "icon/icon.h"

/*
 * Create the item following the QGraphicsView constructor
 */
View::View(QWidget *parent) : QGraphicsView{parent}
{
    setAlignment(Qt::AlignTop | Qt::AlignLeft);
    this->setRenderHints(QPainter::Antialiasing |
                         QPainter::SmoothPixmapTransform);
    this->setBackgroundBrush(Qt::white);
}

void View::setGScene(Scene *scene)
{
    this->setScene(scene);
    this->gScene = scene;
}

/*
 * Configure the event of clicking the View to print the location
 * of the mouse at the moment.
 */
void View::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
}

