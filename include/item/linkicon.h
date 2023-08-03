#ifndef LINK_H
#define LINK_H

#include "item/icon.h"
#include <QGraphicsPolygonItem>
#include <QPen>

///
/// @brief A class for creating a link between machines/clusters
///
/// It should have two \link Icon \endlink connected to itself, and obeys
/// their behavior; it moves when they move, for example.
///
/// @see Icon
class LinkIcon : public QGraphicsPolygonItem
{
public:
    LinkIcon(const char *name);
    /* LinkIcon(const char *name, QGraphicsItem *parent = nullptr); */
    ~LinkIcon();

    unsigned     id;
    Icon        *begin; ///< the \link Icon \endlink that the link comes from
    Icon        *end;   ///< the \link Icon \endlink that the link goes to
    void         mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void         updatePositions();
    std::string *getName();
    void         draw(Icon *b, Icon *e);

protected:
    void updateArrow();
    void paint(QPainter                       *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget                        *widget) override;

    void select();

private:
    std::string          *name; ///< the name of the \link Link \endlink
    QGraphicsPolygonItem *arrow;
    QPen                  linkPen;
};

#endif
