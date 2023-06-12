#pragma once

#include "qgraphicsitem.h"
#include "icon.h"
#include <QObject>
#include <string>

class ClusterIcon : public Icon
{
    Q_OBJECT
public:
    explicit ClusterIcon(const char *name, QGraphicsItem *parent = nullptr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void select();

private:
    const char *iconPath = ":icons/cluster.png";
    const char *iconPathSelected = ":icons/clusterSelected.png";

signals:
};

