#pragma once

#include "icon.h"
#include "item/machineicon.h"
#include "qgraphicsitem.h"
#include <QObject>
#include <deque>
#include <string>

class ClusterIcon : public Icon
{
    Q_OBJECT
public:
    explicit ClusterIcon(const char *name, QGraphicsItem *parent = nullptr);

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

private:
    std::deque<MachineIcon> *machines;
    std::deque<Link>        *innerLinks;
};
