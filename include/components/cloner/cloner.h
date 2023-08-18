#pragma once

#include <memory>
#include "components/component.h"

class Schema;

class Cloner {
    public:
    virtual Component *clone(Schema *schema) = 0;
};
