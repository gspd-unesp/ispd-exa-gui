#ifndef SCENE_H
#define SCENE_H

#include "components/machine.h"
#include "icon/icon.h"
#include "qglobal.h"
#include "qvector.h"
#include "window/users.h"
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
class LinkIcon;
class DrawingTable;

class Scene : public QGraphicsScene
{

    Q_OBJECT

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

public:
    Scene(DrawingTable *parent);
    QVector<Icon *>     *icons;
    QVector<LinkIcon *> *links;

    void addIcon(Icon *icon, QPointF pos = QPointF(0, 0));
    void drawBackgroundLines();

    PICK_OP pickOp;

    QLabel *machineDescriptionLabel;

private:
    DrawingTable      *table;
    Schema            *schema;
    Connection        *lBegin;
    Connection        *lEnd;
    void               addLink(Link *link);
    Connection        *whichConnection(QPointF pos);
    std::string        getNewMachineName();
    std::string        getNewLinkName();
    std::string        getNewClusterName();
    void               removeMachine(Machine *machine);
    void               removeLink(Link *link);
    void               removeItemIcon(Item *item);
    void               deleteItems();
    UserWindow        *userWindow;
    QPointF            startSelection;
    QGraphicsRectItem *selectionRect;

    void selectionArea(QGraphicsSceneMouseEvent *event);
signals:
    void clicked(QPointF position);
};

#endif
