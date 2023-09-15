#include "components/link.h"
#include "components/cloner/linkcloner.h"
#include "components/connectable.h"
#include "components/connectable.h"
#include "icon/linkicon.h"
#include "qdebug.h"
#include <iterator>
#include <memory>

Link::Link(Schema *schema, LinkConfiguration conf, LinkConnections connections)
    : schema(schema), connections(connections)
{
    this->conf        = std::make_unique<LinkConfiguration>(conf);

    this->icon = std::make_unique<LinkIcon>(this);
    this->addLine();
}

Link::~Link()
{
    qDebug() << "Deleting Link";

    this->connections.begin->removeConnectedLink(this);
    this->connections.end->removeConnectedLink(this);

    qDebug() << "|- End of Link destructor.";
}

void Link::addLine()
{
    this->connections.begin->addConnectedLink(this);
    this->connections.end->addConnectedLink(this);

    this->icon->draw();
}

void Link::showConfiguration()
{
    // TODO IMPLEMENT
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
