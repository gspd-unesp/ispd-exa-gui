#pragma once

#include "icon.h"
#include "qgraphicsitem.h"
#include "window/schemawindow.h"
#include <QObject>
#include <deque>
#include <string>

class Schema;
class MachineIcon;

class SchemaIcon : public Icon
{
    Q_OBJECT
public:
    explicit SchemaIcon(const char    *name,
                        Schema        *owner  = nullptr,
                        QGraphicsItem *parent = nullptr);
    Schema *owner;
    SchemaWindow *window;

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

private:
    std::deque<MachineIcon> *machines;
    std::deque<Link>        *innerLinks;
};
