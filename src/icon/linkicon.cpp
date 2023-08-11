#include "icon/linkicon.h"
#include "components/connection.h"
#include "components/link.h"
#include "icon/icon.h"
#include "qdebug.h"
#include "qgraphicsitem.h"
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
QPointF getMiddleOfIcon(Icon *a)
{
    qreal y = (a->pos().y() + ((qreal)a->pixmap().height() / 2));
    qreal x = (a->pos().x() + ((qreal)a->pixmap().width() / 2));

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
    qDebug() << "Is it here?";
    this->begin = this->owner->connections.begin->getIcon();
    this->end   = this->owner->connections.end->getIcon();
}

LinkIcon::~LinkIcon()
{
    qDebug() << "Deleting the link icon of" << this->owner->name.c_str();
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
void LinkIcon::updatePositions()
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
    select(); // Call the select function to toggle the color
    QGraphicsPolygonItem::mousePressEvent(event);
}

void LinkIcon::select()
{
    if (begin->isSelected()) {
        begin->setSelected(true);
        end->setSelected(true);
        linkPen.setColor(QColor(9, 132, 227));
        this->setPen(linkPen);
    }
    else {
        begin->setSelected(false);
        end->setSelected(false);
        linkPen.setColor(QColor(245, 69, 55));
        this->setPen(linkPen);
    }
}
