#pragma once

#include "components/conf/switchconfiguration.h"
#include <memory>
#include <string>

class Schema;
class Switch;
class PixmapIcon;
class SwitchConfiguration;

class SwitchBuilder
{
public:
    SwitchBuilder() = default;
    SwitchBuilder          *setSchema(Schema *schema);
    SwitchBuilder          *setConf(SwitchConfiguration *conf);
    std::unique_ptr<Switch> build();

private:
    Schema              *schema;
    PixmapIcon          *icon;
    SwitchConfiguration *conf;
};
