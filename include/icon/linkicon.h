#ifndef LINK_H
#define LINK_H

#include "icon/icon.h"
#include <QGraphicsPolygonItem>
#include <QPen>
#include <memory>
#include <optional>

///
/// @brief A class for creating a link between machines/clusters
///
/// It should have two \link Icon \endlink connected to itself, and obeys
/// their behavior; it moves when they move, for example.
///
/// @see Icon
class LinkIcon : public Icon, public QGraphicsPolygonItem
{
public:
    LinkIcon(Link *owner, const char *name);
    ~LinkIcon();

    Link        *owner;
    unsigned     id;
    Icon        *begin; ///< the \link Icon \endlink that the link comes from
    Icon        *end;   ///< the \link Icon \endlink that the link goes to
    void         mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void         updatePositions();
    std::string *getName();
    void         draw();

protected:
    void updateArrow();
    void paint(QPainter                       *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget                        *widget) override;

    void select();

private:
    std::unique_ptr<std::string> name; ///< the name of the \link Link \endlink
    QGraphicsPolygonItem        *arrow;
    QPen                         linkPen;
};

#endif
