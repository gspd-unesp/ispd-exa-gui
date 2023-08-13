#pragma once

#include "icon/icon.h"

template <class IconT>
class Item {
    public: 
        virtual void showConfiguration() = 0;
        virtual IconT *getIcon() = 0;
};
