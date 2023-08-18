#pragma once

class Item;
class QRectF;

class Icon
{
public:
    virtual ~Icon()                                              = default;
    virtual Item *getOwner()                                     = 0;
    virtual void  toggleChoosen()                                = 0;
    virtual bool  isChosen()                                     = 0;
    virtual void  toggleChosenIfInside(QRectF selectionAreaRect) = 0;
    virtual void  updatePosition()                               = 0;
};
