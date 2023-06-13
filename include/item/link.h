#ifndef LINK_H
#define LINK_H
#include "icon.h"
#include "qgraphicsitem.h"

class Icon;

///
/// @brief A class for creating a link between machines/clusters
///
/// It should have two \link Icon \endlink connected to itself, and obeys the
/// their behavior, it moves when they move, for example.
///
/// @see Icon
class Link : public QGraphicsPolygonItem
{
public:
    explicit Link(char const *name, Icon *b, Icon *e);

    Icon *begin; ///< the \link Icon \endlink that the link comes from
    Icon *end;   ///< the \link Icon \endlink that the link goes to

    void updatePositions();

protected:
    void updateArrow();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    std::string *name; ///< the name of the \link Link \endlink
    QGraphicsPolygonItem* arrow;
};

#endif
