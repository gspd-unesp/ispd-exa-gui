#ifndef LINK_H
#define LINK_H

#include "icon/pixmapicon.h"
#include "components/link.h"
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
class LinkIcon : public QGraphicsPolygonItem, public Icon<Link>
{
public:
    explicit LinkIcon(Link *owner);
    ~LinkIcon();

    Link        *owner;
    PixmapIcon        *begin; ///< the \link Icon \endlink that the link comes from
    PixmapIcon         *end;   ///< the \link Icon \endlink that the link goes to
    void         mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void         updatePositions();
    std::string *getName();
    void         draw();
    Link *getOwner() override;
    void  toggleSelect() override;

protected:
    void updateArrow();
    void paint(QPainter                       *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget                        *widget) override;

    void select();

private:
    QGraphicsPolygonItem        *arrow;
    QPen                         linkPen;
};

#endif
