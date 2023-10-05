#pragma once

#include <memory>
#include <string>

class Schema;
class ConnectableSet;
class PixmapIcon;
class ConnectableSetConfiguration;

class ConnectableSetBuilder
{
public:
    ConnectableSetBuilder() = default;

    ConnectableSetBuilder *setSchema(Schema *baseSchema);
    ConnectableSetBuilder *setConf(ConnectableSetConfiguration const &baseConf);
    std::unique_ptr<ConnectableSet> build();

private:
    Schema                                      *schema;
    std::unique_ptr<ConnectableSetConfiguration> conf;
};
