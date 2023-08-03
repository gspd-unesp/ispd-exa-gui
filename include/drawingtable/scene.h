#ifndef SCENE_H
#define SCENE_H

#include "item/icon.h"
#include "item/machine.h"
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
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);


public:
    explicit Scene(QObject *parent = nullptr);
    QVector<Icon *>     *icons;
    QVector<LinkIcon *> *links;

    void addIcon(Icon *icon, QPointF pos = QPointF(0, 0));
    void drawBackgroundLines();

    PICK_OP pickOp;

    QLabel *machineDescriptionLabel;

private:
    DrawingTable *table;
    Schema       *schema;
    Item         *lBegin;
    Item         *lEnd;
    void          addLink(LinkIcon *linkIcon, Item *a, Item *b);
    Item         *whichMachine(QPointF pos);
    std::string   getNewMachineName();
    std::string   getNewLinkName();
    std::string   getNewClusterName();
    void          removeMachine(Machine *machine);
    void          removeLink(Link *link);
    void          removeItemIcon(Item *item);
    UserWindow   *userWindow;
    QPointF startSelection;
    QGraphicsRectItem *selectionRect;

    void selectionArea(QGraphicsSceneMouseEvent *event);
signals:
    void clicked(QPointF position);
};

#endif
