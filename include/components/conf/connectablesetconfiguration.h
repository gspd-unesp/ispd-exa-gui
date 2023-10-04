#include "components/conf/itemconfiguration.h"

class ConnectableSetConfiguration : public ItemConfiguration
{
public:
    std::string getName() const override;
    void        setName(std::string_view const &name) override;

private:
    std::string name;
};
