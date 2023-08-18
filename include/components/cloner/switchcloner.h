#pragma once 

#include "components/cloner/connectablecloner.h"

class Switch;
class SchemaCloner;
class Connectable;

class SwitchCloner : public ConnectableCloner {
    public:
    SwitchCloner(Switch *base, SchemaCloner *parent);
    Connectable *clone(Schema *schema);
};
