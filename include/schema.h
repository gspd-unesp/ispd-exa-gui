#pragma once

#include <map>

class SchemaIcon;
class LinkLoad;
class MachineLoad;

typedef struct IDS
{
    unsigned schemaId;
    unsigned machineId;
    unsigned linkId;
    unsigned switchId;
} ids;

class Schema
{
public:
    ids *schemaIds;
    Schema(Schema *parent = nullptr);

    unsigned    id;
    SchemaIcon *icon;

    std::map<unsigned, MachineLoad *> *machines;
    std::map<unsigned, LinkLoad *>    *links;
    std::map<unsigned, Schema *>      *schemas;

    unsigned allocateNewMachine();
    unsigned allocateNewLink();
    unsigned allocateNewSchema();
    void  deleteMachine(unsigned machineId);
    void  deleteLink(unsigned linkId);
};
