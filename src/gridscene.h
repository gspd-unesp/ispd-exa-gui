#ifndef GRIDSCENE_H
#define GRIDSCENE_H

#include <QGraphicsScene>
#include <QWidget>

class GridScene : public QGraphicsScene
{
    Q_OBJECT

  public:
    explicit GridScene(QObject *parent = nullptr);


  signals:
    void clicked(QPointF position);
};

#endif // GRIDSCENE_H
