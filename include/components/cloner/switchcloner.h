#pragma once

class Switch;
class SchemaCloner;

class SwitchCloner {
public:
    SwitchCloner(Switch *base, SchemaCloner *parent);
private:
    Switch *base;
};

