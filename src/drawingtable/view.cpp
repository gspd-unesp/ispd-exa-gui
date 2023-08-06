#include "drawingtable/view.h"
#include "drawingtable/scene.h"
#include <QDebug>
#include <QGraphicsView>
#include <QMouseEvent>
#include "item/icon.h"

/*
 * Create the item following the QGraphicsView constructor
 */
View::View(QWidget *parent) : QGraphicsView{parent}
{
    setAlignment(Qt::AlignTop | Qt::AlignLeft);
    this->setRenderHints(QPainter::Antialiasing |
                         QPainter::SmoothPixmapTransform);
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
    qDebug() << event->pos().x();
    qDebug() << event->pos().y();

    if (event->button() == Qt::RightButton) {
        qDebug() << "Custom view clicked with right.";
    }

    if (event->button() == Qt::LeftButton) {
        qDebug() << "Custom view clicked with left.";
    }

    // Deselect all icons if the clicked area has no icons
    if (event->modifiers() & Qt::ShiftModifier) {
    } else {
        QGraphicsItem* clickedItem = itemAt(event->pos().x(), event->pos().y());
        if (!clickedItem) {
            for (auto item : this->items()) {
                if (Icon* icon = dynamic_cast<Icon*>(item)) {
                    icon->selection(false);
                }
            }
        }
    }
    QGraphicsView::mousePressEvent(event);
}

