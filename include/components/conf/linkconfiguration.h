#pragma once

#include <string>

class LinkConfiguration
{
public:
    explicit LinkConfiguration(std::string_view const name);

    std::string getName() const;
    void        setName(std::string_view const newName);

private:
    unsigned    id;
    std::string name;
};
