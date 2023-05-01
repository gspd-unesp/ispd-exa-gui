#ifndef GRIDITEM_H
#define GRIDITEM_H

#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QWidget>
#include <QObject>
#include "ui_mainwindow.h"


class GridItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
  public:
    GridItem(const QPixmap &pixmap, Ui::MainWindow *ui, QGraphicsItem *parent = nullptr);

  protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  private:
    QString positionString;
    Ui::MainWindow *ui;
};

#endif // GRIDITEM_H
