#include "components/link.h"
#include "components/cloner/linkcloner.h"
#include "components/connection.h"
#include "icon/linkicon.h"
#include "qdebug.h"
#include <iterator>
#include <memory>

Link::Link(Schema *schema, LinkConfiguration *conf, LinkConnections connections)
{
    this->conf        = std::unique_ptr<LinkConfiguration>(conf);
    this->connections = connections;
    this->schema      = schema;

    this->icon = std::make_unique<LinkIcon>(this);
    this->addLine();
}

Link::~Link()
{
    qDebug() << "Deleting Link";

    this->connections.begin->removeConnectedLink(this);
    this->connections.end->removeConnectedLink(this);
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

Icon *Link::getIcon()
{
    return this->icon.get();
}

LinkConfiguration *Link::getConf()
{
    return this->conf.get();
}

Cloner *Link::cloner()
{
    return new LinkCloner(this, nullptr);
}
