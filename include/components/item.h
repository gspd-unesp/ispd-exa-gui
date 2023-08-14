#pragma once

#include "icon/icon.h"

template <class IconT>
class Item {
    public: 
        virtual ~Item() = default;
        virtual void showConfiguration() = 0;
        virtual IconT *getIcon() = 0;
};
