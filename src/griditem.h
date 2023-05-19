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
    //GridItem(const QPixmap &pixmap, Ui::MainWindow *ui, QGraphicsItem *parent = nullptr);
    explicit GridItem(QPixmap pixmap, QGraphicsItem *parent = nullptr);
    static GridItem *fromPath(const char *iconPath, QGraphicsItem *parent = nullptr);

  protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  private:
    QString positionString;
    Ui::MainWindow *ui;
    std::string name;
};

#endif // GRIDITEM_H
