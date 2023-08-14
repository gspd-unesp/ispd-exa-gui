#pragma once

template <class OwnerT>
class Icon
{
public:
    virtual ~Icon() = default;
    virtual OwnerT *getOwner() = 0;
    virtual void  toggleChoosen() = 0;
    virtual bool  isChosen() = 0;
};
