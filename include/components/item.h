#pragma once

#include "components/conf/itemconfiguration.h"

template <class IconT>
class Item {
    public: 
        virtual ~Item() = default;
        virtual void showConfiguration() = 0;
        virtual IconT *getIcon() = 0;
        virtual ItemConfiguration *getConf() = 0;
};
