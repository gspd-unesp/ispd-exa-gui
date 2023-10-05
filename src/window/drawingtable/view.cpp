#include "window/drawingtable/view.h"
#include "window/drawingtable/scene.h"
#include <QDebug>
#include <QGraphicsView>
#include <QMouseEvent>

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

void View::wheelEvent(QWheelEvent *event)
{
    if (event->modifiers() & Qt::ControlModifier) {
        // zoom
        const ViewportAnchor anchor = transformationAnchor();
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        int   angle = event->angleDelta().y();
        qreal factor;
        if (angle > 0) {
            factor = 1.1;
        }
        else {
            factor = 0.9;
        }
        scale(factor, factor);
        setTransformationAnchor(anchor);
    }
    else {
        QGraphicsView::wheelEvent(event);
    }
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
