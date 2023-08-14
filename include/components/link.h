#pragma once

#include "components/item.h"
#include <memory>
#include <string>

class LinkIcon;
class Connection;
class Schema;

struct LinkConnections
{
    Connection *begin;
    Connection *end;
};

class Link : public Item<LinkIcon>
{
public:
    explicit Link(Schema         *schema,
                  unsigned        id,
                  const char     *name,
                  LinkConnections connections);
    ~Link() override;

    void  addLine();
    void  draw();
    void  showConfiguration() override;
    LinkIcon *getIcon() override;

    Schema *schema;

    LinkConnections connections;

    std::string name;

    unsigned                  id;
    std::unique_ptr<LinkIcon> icon;
};
