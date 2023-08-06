#include "components/link.h"
#include "components/connection.h"
#include "components/item.h"
#include "icon/icon.h"
#include "icon/linkicon.h"
#include "qdebug.h"
#include <iterator>

Link::Link(unsigned id)
{
    this->id = id;
}

Link::~Link()
{}

void Link::addLine(Connection *a, Connection *b)
{
    this->begin = a;
    this->end   = b;

    qDebug() << "Adicionado begin e end ao link " << this->id;

    this->begin->get_connected_links()->insert(std::pair(this->id, this));
    this->end->get_connected_links()->insert(std::pair(this->id, this));

    qDebug() << "Adicionado o link " << this->id << " ao Item begin e end.";

    this->icon->draw(this->begin->getIcon(), this->end->getIcon());

    qDebug() << "Adicionado o icon do link  " << this->id << " a grid.";
}
