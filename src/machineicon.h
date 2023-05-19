#pragma once

#include "src/icon.h"
#include <QObject>
#include <string>

class MachineIcon : public Icon
{
    Q_OBJECT
public:
    MachineIcon(const char *name, QGraphicsItem *parent = nullptr);
    const char *iconPath = ":icons/pc.png";

signals:
};
