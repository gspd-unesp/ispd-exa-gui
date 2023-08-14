#pragma once
#include <string>

class ItemConfiguration
{
public:
    virtual ~ItemConfiguration() = default;

    virtual unsigned    getId()                   = 0;
    virtual void        setId(unsigned id)        = 0;
    virtual std::string getName()                 = 0;
    virtual void        setName(std::string name) = 0;
};
