#pragma once

#include "icon.h"
#include <QObject>
#include <string>

class Machine;

class MachineIcon : public Icon
{
    Q_OBJECT
public:
    explicit MachineIcon(Machine       *owner,
                QGraphicsItem *parent = nullptr);

    MachineIcon(MachineIcon& icon);
protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    Machine *owner;
};
