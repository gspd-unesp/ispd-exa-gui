#pragma once

#include "icon.h"
#include "qgraphicsitem.h"
#include "window/schemawindow.h"
#include <QObject>
#include <deque>
#include <memory>
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
    SchemaIcon(SchemaIcon &icon);
    std::unique_ptr<SchemaWindow> window;

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    Schema *owner;
};
