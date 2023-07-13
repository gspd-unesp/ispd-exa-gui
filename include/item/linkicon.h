#pragma once

#include "icon.h"
#include <QObject>
#include <string>

class LinkIcon : public Icon
{
    Q_OBJECT
public:
    LinkIcon(const char *name, QGraphicsItem *parent = nullptr);

private:
};


