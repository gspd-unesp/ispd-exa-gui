#include "components/link.h"
#include "components/connection.h"
#include "icon/linkicon.h"
#include "qdebug.h"
#include <iterator>
#include <memory>

Link::Link(Schema         *schema,
           unsigned        id,
           const char     *name,
           LinkConnections connections)
{
    this->id          = id;
    this->connections = connections;
    this->schema      = schema;
    this->name        = name;

    this->icon        = std::make_unique<LinkIcon>(this);
    this->addLine();
}

Link::~Link()
{
    qDebug() << "Deleting " << this->name.c_str();
}

void Link::addLine()
{
    this->connections.begin->addConnectedLink(this);
    this->connections.end->addConnectedLink(this);

    this->icon->draw();
}

void Link::showConfiguration() {
    // TODO IMPLEMENT
}

LinkIcon *Link::getIcon() {
    return this->icon.get();
}
