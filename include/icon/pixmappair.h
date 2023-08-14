#pragma once 

#include "qdebug.h"
#include "qpixmap.h"
#include "utils/iconSize.h"

class PixmapPair
{
public:
    PixmapPair(const char * const normalPath, const char * const selectedPath) {
        this->normal = QPixmap(normalPath).scaled(iconSize);
        this->selected = QPixmap(selectedPath).scaled(iconSize);
    }

    QPixmap getNormal()
    {
        return this->normal;
    }
    
    QPixmap getSelected()
    {
        return this->selected;
    }

private:
    QPixmap normal;
    QPixmap selected;
};
