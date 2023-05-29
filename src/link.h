#pragma once 

#include "icon.h"
#include "qpolygon.h"

class Link{
    public:
        explicit Link(Icon *a, Icon *b);
        QPolygonF *line;

    private:
};
