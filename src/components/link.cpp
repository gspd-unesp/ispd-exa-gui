#include "components/link.h"
#include "components/cloner/linkcloner.h"
#include "components/connectable.h"
#include "icon/linkicon.h"
#include "qdebug.h"
#include <iterator>
#include <memory>

Link::Link(Schema *schema, LinkConfiguration conf, LinkConnections connections)
    : schema(schema), connections(connections)
{
    this->conf = std::make_unique<LinkConfiguration>(conf);

    this->icon = std::make_unique<LinkIcon>(this);
}

Link::~Link() = default;

void Link::showConfiguration()
{
}

LinkIcon *Link::getIcon()
{
    return this->icon.get();
}

LinkConfiguration *Link::getConf()
{
    return this->conf.get();
}

std::unique_ptr<LinkCloner> Link::cloner(SchemaCloner *parent)
{
    return std::make_unique<LinkCloner>(this, parent);
}

unsigned Link::getId() const
{
    return this->id;
}

void Link::setId(unsigned newId)
{
    this->id = newId;
}
