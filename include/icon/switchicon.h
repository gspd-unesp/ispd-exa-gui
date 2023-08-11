#pragma once

#include "icon/icon.h"

class Schema;
class Switch;

class SwitchIcon : public Icon
{
    Q_OBJECT
public:
    explicit SwitchIcon(Switch        *owner,
               QGraphicsItem *parent = nullptr);

private:
    unsigned id;
    Switch  *owner;
};
