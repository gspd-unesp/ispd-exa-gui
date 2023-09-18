#pragma once
#include "components/conf/itemconfiguration.h"

class SwitchConfiguration : public ItemConfiguration
{
public:
    explicit SwitchConfiguration(std::string_view const &name);

    std::string getName() const override;
    void        setName(std::string_view const &newName) override;

private:
    std::string name = "";
};
