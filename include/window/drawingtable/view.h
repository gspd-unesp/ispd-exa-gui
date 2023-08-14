#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include <QWidget>

class Scene;
class DrawingTable;

class View : public QGraphicsView
{
    Q_OBJECT
    Scene *gScene;

public:
    View(QWidget *parent = nullptr);
    void setGScene(Scene *scene);
protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif
