#ifndef SCENE_H
#define SCENE_H

#include "components/cloner/machinecloner.h"
#include "components/machine.h"
#include "qglobal.h"
#include "window/users.h"
#include <QGraphicsScene>
#include <QWidget>

typedef enum PICK_OP
{
    NONE,
    PC,
    SCHEMA,
    LINK,
    SWITCH
} PICK_OP;

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
    QVector<LinkIcon *> *links;

    void addIcon(PixmapIcon *icon, QPointF pos = QPointF(0, 0));
    void drawBackgroundLines();

    PICK_OP pickOp;

    QLabel *machineDescriptionLabel;

private:
    QPointF            getScenePosition();
    DrawingTable      *table;
    Schema            *schema;
    Connection        *lBegin;
    Connection        *lEnd;
    void               addLink(Link *link);
    Connection        *whichConnection(QPointF pos);
    void               removeLink(Link *link);
    void               deleteItems();
    UserWindow        *userWindow;
    QPointF            startSelection;
    QGraphicsRectItem *selectionRect;
    MachineCloner     *mCloner;
    /* Cloner            *sCloner; */
    /* Cloner            *sCloner; */

    void selectionArea(QGraphicsSceneMouseEvent *event);
signals:
    void clicked(QPointF position);
};

#endif
