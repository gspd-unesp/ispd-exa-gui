#include "gridview.h"
#include <QDebug>
#include <QGraphicsView>
#include <QMouseEvent>


GridView::GridView(QWidget* parent) {}

void
GridView::mousePressEvent(QMouseEvent* event)
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
