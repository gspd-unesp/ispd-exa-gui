#include "components/cloner/switchcloner.h"
#include "components/cloner/schemacloner.h"
#include "components/switch.h"

SwitchCloner::SwitchCloner(Switch *base, SchemaCloner *parent)
{
    this->base   = base;
    this->parent = parent;
}
