#pragma once

#include "components/item.h"
#include <memory>

class Cloner {
    public:
    virtual std::unique_ptr<Item> clone() = 0;
};
