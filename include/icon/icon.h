#pragma once

class Component;
class QRectF;

class Icon
{
public:
    virtual ~Icon()                                              = default;
    virtual Component *getOwner()                                     = 0;
    virtual void  toggleChoosen()                                = 0;
    virtual bool  isChosen()                                     = 0;
    virtual void  toggleChosenIfInside(QRectF selectionAreaRect) = 0;
    virtual void  updatePosition()                               = 0;
};
