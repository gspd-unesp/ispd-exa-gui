#ifndef GRIDSCENE_H
#define GRIDSCENE_H

#include "qglobal.h"
#include "qvector.h"
#include "icon.h"
#include <QGraphicsScene>
#include <QWidget>

typedef enum PICK_OP
{
    NONE,
    PC,
    CLUSTER,
    LINK
} PICK_OP;

class GridScene : public QGraphicsScene
{

    Q_OBJECT

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

public:
    explicit GridScene(QObject *parent = nullptr);
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

signals:
    void clicked(QPointF position);
};

#endif // GRIDSCENE_H
