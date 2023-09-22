#pragma once
#include "components/conf/itemconfiguration.h"

class SchemaConfiguration : public ItemConfiguration
{
public:
    explicit SchemaConfiguration(std::string_view const &name);

    std::string getName() const override;
    void        setName(std::string_view const &newName) override;

private:
    std::string name = "";
};
