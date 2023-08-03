#include "item/link.h"
#include "item/icon.h"
#include "item/item.h"
#include "item/linkicon.h"
#include <iterator>

Link::Link(unsigned id)
{
    this->id = id;
}

Link::~Link()
{
}

void Link::addLine(Item *a, Item *b) {
    this->begin = a;
    this->end = b;

    this->icon->draw(begin->getIcon(), end->getIcon());
}
