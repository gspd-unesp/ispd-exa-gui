#pragma once

#include "item/machine.h"
#include <map>

class SchemaIcon;
class Link;
class Machine;

typedef struct IDS
{
    unsigned schemaId;
    unsigned machineId;
    unsigned linkId;
    unsigned switchId;
} ids;

class Schema : public Item
{
public:
    ids *schemaIds;
    Schema(Schema *parent = nullptr);

    Schema(const Schema &)                = default;
    Schema(Schema &&)                     = default;
    Schema     &operator=(const Schema &) = default;
    Schema     &operator=(Schema &&)      = default;
    unsigned    id;
    SchemaIcon *icon;

    std::map<unsigned, Machine *> *machines;
    std::map<unsigned, Link *>    *links;
    std::map<unsigned, Schema *>  *schemas;

    unsigned allocateNewMachine();
    unsigned allocateNewLink();
    unsigned allocateNewSchema();
    void     deleteMachine(unsigned machineId);
    void     deleteLink(unsigned linkId);

    void     showConfiguration();
    Icon     *getIcon();
};
