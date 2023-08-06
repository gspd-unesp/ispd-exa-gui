#ifndef SCENE_H
#define SCENE_H

#include "item/icon.h"
#include "qglobal.h"
#include "window/users.h"
#include "qvector.h"
#include <QGraphicsScene>
#include <QWidget>

typedef enum PICK_OP
{
    NONE,
    PC,
    SCHEMA,
    LINK
} PICK_OP;

class MachineIcon;

class Scene : public QGraphicsScene
{

    Q_OBJECT

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);


public:
    explicit Scene(QObject *parent = nullptr);
    QVector<Icon *> *icons;
    QVector<Link *> *links;

    void addIcon(Icon *icon, QPointF pos = QPointF(0, 0));
    void drawBackgroundLines();

    PICK_OP pickOp;

    QLabel *machineDescriptionLabel;

private:
    Icon           *lBegin;
    Icon           *lEnd;
    void            addLink(Link *link, Icon *a, Icon *b);
    Icon           *whichMachine(QPointF pos);
    std::string     getNewMachineName();
    std::string     getNewLinkName();
    std::string     getNewClusterName();
    void            removeMachine(MachineIcon *icon);
    void            removeLink(Link *link);
    UserWindow      *userWindow;
    QPointF startSelection;
    QGraphicsRectItem *selectionRect;

    void selectionArea(QGraphicsSceneMouseEvent *event);
signals:
    void clicked(QPointF position);
};

#endif
