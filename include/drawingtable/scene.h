#ifndef SCENE_H
#define SCENE_H

#include "qglobal.h"
#include "qvector.h"
#include "item/icon.h"
#include <QGraphicsScene>
#include <QWidget>

typedef enum PICK_OP
{
    NONE,
    PC,
    CLUSTER,
    LINK
} PICK_OP;

class Scene : public QGraphicsScene
{

    Q_OBJECT

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

public:
    explicit Scene(QObject *parent = nullptr);
    QVector<Icon *> *items;
    void             addIcon(Icon *icon, QPointF pos = QPointF(0, 0));
    void             drawBackgroundLines();

    PICK_OP          pickOp;

    QLabel           *machineDescriptionLabel;

private:
    int pIndex;
    int cIndex;
    int lIndex;
    Icon *lBegin;
    Icon *lEnd;
    void addLink(Icon *a, Icon *b);
    Icon *whichMachine(QPointF pos);
    std::string getNewMachineName();
    std::string getNewLinkName();
    std::string getNewClusterName();
    QGraphicsScene* scene;
signals:
    void clicked(QPointF position);
};

#endif
