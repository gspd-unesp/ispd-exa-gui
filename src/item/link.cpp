#include "item/link.h"
#include "item/icon.h"
#include <QGraphicsItem>
#include <QPen>

///
/// Helper function to get the middle point of an icon
///
/// @param a a pointer to an Icon
///
/// @returns the point at the middle of the Icon
///
QPointF getMiddleOfIcon(Icon *a)
{
    qreal y = (a->pos().y() + ((qreal)a->pixmap().height() / 2));
    qreal x = (a->pos().x() + ((qreal)a->pixmap().width() / 2));

    return QPointF(x, y);
}

///
///  @brief Default constructor for Link
///
///  @see Icon
///  @param name  the name of the Link
///  @param b     the Icon that the Link comes from
///  @param e     the Icon that the Link goes to
///
Link::Link(char const *name, Icon *b, Icon *e) : QGraphicsPolygonItem()
{
    this->name  = new std::string(name);
    this->begin = b;
    this->end   = e;

    b->links->append(this);
    e->links->append(this);

    QPen pen;
    pen.setWidth(1);
    pen.setColor(QColor(255, 85, 59, 124));
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    this->setPen(pen);

    QPolygonF newLine;
    newLine << getMiddleOfIcon(this->begin) << getMiddleOfIcon(this->end);

    this->setPolygon(newLine);
}

///
/// @brief Update the position of the Link, suppose to be used when moving
///        an Icon that the Link is connected.
///
void Link::updatePositions()
{
    QPolygonF newLine;
    newLine << getMiddleOfIcon(this->begin) << getMiddleOfIcon(this->end);
    this->setPolygon(newLine);
}
