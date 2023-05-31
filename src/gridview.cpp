#include "gridview.h"
#include "src/gridscene.h"
#include <QDebug>
#include <QGraphicsView>
#include "gridscene.h"
#include <QMouseEvent>

/*
 * Create the item following the QGraphicsView constructor
 */
GridView::GridView(QWidget *parent) : QGraphicsView{parent}
{
    setAlignment(Qt::AlignTop | Qt::AlignLeft);
    this->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
}

void GridView::setGScene(GridScene *scene) {
    this->setScene(scene);
    this->gScene = scene;
}

/*
 * Configure the event of clicking the View to print the location
 * of the mouse at the moment.
 */
void GridView::mousePressEvent(QMouseEvent *event)
{

    qDebug() << event->pos().x();
    qDebug() << event->pos().y();

    if (event->button() == Qt::RightButton) {
        qDebug() << "Custom view clicked with right.";
    }

    if (event->button() == Qt::LeftButton) {
        qDebug() << "Custom view clicked with left.";
    }
    QGraphicsView::mousePressEvent(event);
}
