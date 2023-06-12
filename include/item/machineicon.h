#pragma once

#include "icon.h"
#include <QObject>
#include <string>

class MachineIcon : public Icon
{
    Q_OBJECT
public:
    MachineIcon(const char *name, QGraphicsItem *parent = nullptr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void select();

private:
    const char *iconPath = ":icons/pc.png";
    const char *iconPathSelected = ":icons/pcSelected.png";

signals:
};
