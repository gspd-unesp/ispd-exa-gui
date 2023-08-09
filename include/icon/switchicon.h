#pragma once

#include "icon/icon.h"

class Schema;
class Switch;

class SwitchIcon : public Icon
{
    Q_OBJECT
public:
    SwitchIcon(const char    *name,
               Switch        *owner,
               QGraphicsItem *parent = nullptr);

private:
    unsigned id;
    Switch  *owner;
};
