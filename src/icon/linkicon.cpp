#include "icon/linkicon.h"
#include "components/connectable.h"
#include "components/connectable.h"
#include "components/link.h"
#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsEffect>
#include <QGraphicsItem>
#include <QPainter>
#include <QPen>
#include <algorithm>
#include <cmath>
#include <memory>

///
/// Helper function to get the middle point of an icon
///
/// @param a a pointer to an Icon
///
/// @returns the point at the middle of the Icon
///
QPointF getMiddleOfIcon(PixmapIcon *a)
{
    qreal y = (a->pos().y() + (static_cast<qreal>(a->pixmap().height()) / 2));
    qreal x = (a->pos().x() + (static_cast<qreal>(a->pixmap().width()) / 2));

    return QPointF(x, y);
}

///
///  @brief Default constructor for Link
///
///  @see Link
///  @param owner  the Link that owns this icon.
///
LinkIcon::LinkIcon(Link *owner) : QGraphicsPolygonItem()
{
    this->owner = owner;
    this->begin = this->owner->connections.begin->getIcon();
    this->end   = this->owner->connections.end->getIcon();
}

LinkIcon::~LinkIcon()
{
    qDebug() << "Deleting the linkicon";
}

void LinkIcon::draw()
{
    // QPen pen;
    linkPen.setWidth(2);
    linkPen.setColor(QColor(9, 132, 227));
    linkPen.setCapStyle(Qt::RoundCap);
    linkPen.setJoinStyle(Qt::RoundJoin);
    linkPen.setCosmetic(true); // Suaviza as bordas da linha

    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect();
    shadowEffect->setColor(
        QColor(0, 0, 0, 100));      // Cor e transparência da sombra
    shadowEffect->setBlurRadius(4); // Raio do efeito de sombreamento
    shadowEffect->setOffset(2); // Deslocamento da sombra em relação à linha
    this->setGraphicsEffect(shadowEffect);

    this->setPen(linkPen);

    QPolygonF newLine;
    newLine << getMiddleOfIcon(this->begin) << getMiddleOfIcon(this->end);

    this->setPolygon(newLine);
    this->setZValue(-1);
}

///
/// @brief Update the position of the Link, suppose to be used when moving
///        an Icon that the Link is connected.
///
void LinkIcon::updatePosition()
{
    QPolygonF newLine;

    newLine << getMiddleOfIcon(this->begin) << getMiddleOfIcon(this->end);

    this->setPolygon(newLine);
}

void LinkIcon::paint(QPainter                       *painter,
                     const QStyleOptionGraphicsItem *option,
                     QWidget                        *widget)
{
    QGraphicsPolygonItem::paint(painter, option, widget);

    QLineF line(getMiddleOfIcon(begin), getMiddleOfIcon(end));
    QLineF norm = line.normalVector().unitVector();

    qreal   arrowSize = 5;
    qreal   angle     = std::atan2(-norm.dy(), norm.dx());
    QPointF arrowP1   = line.p2() - QPointF(sin(angle - M_PI / 3) * arrowSize,
                                          cos(angle - M_PI / 3) * arrowSize);
    QPointF arrowP2   = line.p2() - QPointF(sin(angle + M_PI / 3) * arrowSize,
                                          cos(angle + M_PI / 3) * arrowSize);

    painter->setBrush(QColor(9, 132, 227));
    painter->drawPolygon(QPolygonF() << line.p2() << arrowP1 << arrowP2);
}

void LinkIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    toggleChoosen(); // Call the select function to toggle the color
    QGraphicsPolygonItem::mousePressEvent(event);
}

Link *LinkIcon::getOwner()
{
    return this->owner;
}
void LinkIcon::toggleChoosen()
{
    if (this->chose) {
        QPen pen;
        pen.setColor(QColor(9, 132, 227));
        this->setPen(pen);
    }
    else {
        QPen pen;
        pen.setColor(QColor(245, 69, 55));
        this->setPen(pen);
    }

    this->chose = !this->chose;
}

bool LinkIcon::isChosen()
{
    return this->chose;
}

void LinkIcon::toggleChosenIfInside(QRectF area)
{
    if (area.contains(this->sceneBoundingRect()) && !this->isChosen()) {
        this->toggleChoosen();
    }
}
