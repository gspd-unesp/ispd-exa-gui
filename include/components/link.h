#pragma once

#include "components/component.h"
#include "components/conf/linkconfiguration.h"
#include "window/linkconfigurationwindow.h"
#include <memory>
#include <string>
#include "nlohmann/json.hpp"

class LinkIcon;
class LinkCloner;
class SchemaCloner;
class Connectable;
class Schema;

struct LinkConnections
{
    Connectable *begin;
    Connectable *end;

    Connectable *getOtherConnectable(Connectable const *otherConnectable)
    {
        if (otherConnectable == this->begin) {
            return this->end;
        }

        if (otherConnectable == this->end) {
            return this->begin;
        }

        return nullptr;
    }
};

class Link
{
public:
    Link(Schema *schema, LinkConfiguration conf, LinkConnections connections);
    ~Link();

    void                        draw();
    void                        showConfiguration();
    LinkIcon                   *getIcon();
    LinkConfiguration          *getConf();
    std::unique_ptr<LinkCloner> cloner(SchemaCloner *parent);

    Schema *schema;

    LinkConnections connections;

    std::unique_ptr<LinkIcon>                icon;
    std::unique_ptr<LinkConfiguration>       conf;
    std::unique_ptr<LinkConfigurationWindow> window;
    unsigned                                 getId() const;
    void                                     setId(unsigned newId);

private:
    unsigned id;
};

using nlohmann::json;

void to_json(json& j, const Link& m);
void from_json(const json& j, Link& m);
