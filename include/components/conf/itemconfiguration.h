#pragma once
#include <string>

class ItemConfiguration
{
public:
    virtual ~ItemConfiguration() = default;

    virtual std::string getName() const                       = 0;
    virtual void        setName(std::string_view const &name) = 0;
};
