#ifndef GRIDSCENE_H
#define GRIDSCENE_H

#include "qvector.h"
#include "src/icon.h"
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
    void addLink(Icon *a, Icon *b);
    Icon *whichMachine(QPointF pos);

signals:
    void clicked(QPointF position);
};

#endif // GRIDSCENE_H
