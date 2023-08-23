#pragma once
#include "components/conf/itemconfiguration.h"

class LinkConfiguration : public ItemConfiguration
{
public:
    LinkConfiguration(std::string name, unsigned id);
    ~LinkConfiguration() override;

    unsigned    getId() override;
    std::string getName() override;

    void        setId(unsigned id) override;
    void        setName(std::string name) override;

private:
    unsigned id;
    std::string name;
};
