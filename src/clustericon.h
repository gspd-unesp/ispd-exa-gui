#pragma once

#include "qgraphicsitem.h"
#include "src/icon.h"
#include <QObject>
#include <string>

class ClusterIcon : public Icon
{
    Q_OBJECT
public:
    explicit ClusterIcon(const char *name, QGraphicsItem *parent = nullptr);
    const char *iconPath = ":icons/cluster.png";

signals:
};

