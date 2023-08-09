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
    SchemaIcon(const char    *name,
               Schema        *owner,
               QGraphicsItem *parent = nullptr);
    SchemaWindow *window;

private:
    Schema       *owner;
};
