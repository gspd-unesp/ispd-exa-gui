#pragma once
#include "components/conf/itemconfiguration.h"

class SchemaConfiguration : public ItemConfiguration
{
public:
    SchemaConfiguration(unsigned id, std::string name);

    unsigned    getId() override;
    std::string getName() override;

    void        setId(unsigned id) override;
    void        setName(std::string name) override;
};
