#pragma once

#include <memory>
#include "components/item.h"

class Schema;

class Cloner {
    public:
    virtual Item *clone(Schema *schema) = 0;
};
