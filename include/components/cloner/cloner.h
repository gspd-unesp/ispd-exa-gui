#pragma once

#include <memory>

class Schema;

template <class T>
class Cloner {
    public:
    virtual std::unique_ptr<T> clone(Schema *schema) = 0;
};
