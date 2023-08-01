#ifndef VIEW_H
#define VIEW_H

#include "drawingtable/scene.h"
#include <QGraphicsView>
#include <QWidget>

class Scene;
class DrawingTable;

class View : public QGraphicsView
{
    Q_OBJECT

public:
    View(QWidget *parent = nullptr);
    void setGScene(Scene *scene);
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    Scene *gScene;
    QPoint startSelection;
    QGraphicsRectItem *selectionRect;

    friend class DrawingTable;
};

#endif
