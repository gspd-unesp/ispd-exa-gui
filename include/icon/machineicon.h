#pragma once

#include "icon.h"
#include <QObject>
#include <string>

class Machine;

class MachineIcon : public Icon
{
    Q_OBJECT
public:
    MachineIcon(unsigned       id,
                const char    *name,
                Machine       *owner,
                QGraphicsItem *parent = nullptr);

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    Machine *owner;
};
