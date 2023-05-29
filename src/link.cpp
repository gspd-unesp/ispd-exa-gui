#include "link.h"

Link::Link(Icon *a, Icon *b) {
    auto posA = a->pos();
    auto posB = b->pos();

    this->line = new QPolygonF();
    *(this->line) << posA << posB;
}
