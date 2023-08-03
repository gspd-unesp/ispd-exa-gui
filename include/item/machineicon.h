#pragma once

#include "icon.h"
#include <QObject>
#include <string>

class MachineItem;

class MachineIcon : public Icon
{
    Q_OBJECT
public:
    MachineIcon(unsigned id, const char *name, QGraphicsItem *parent = nullptr);

private:
};
