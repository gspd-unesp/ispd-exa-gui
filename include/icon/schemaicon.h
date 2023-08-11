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
    explicit SchemaIcon(Schema        *owner,
               QGraphicsItem *parent = nullptr);
    SchemaIcon(SchemaIcon &icon);

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    Schema *owner;
};
