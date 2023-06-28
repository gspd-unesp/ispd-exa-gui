#include "item/link.h"
#include "item/icon.h"
#include <QGraphicsItem>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsEffect>
#include <QPen>
#include <QPainter>
#include <cmath>

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

    b->isSelected = false;
    e->isSelected = false;

    this->begin = b;
    this->end   = e;


    begin->isSelected = false;
    end->isSelected = false;

    b->links->append(this);
    e->links->append(this);

    // QPen pen;
    linkPen.setWidth(2);
    linkPen.setColor(QColor(9, 132, 227));
    linkPen.setCapStyle(Qt::RoundCap);
    linkPen.setJoinStyle(Qt::RoundJoin);
    linkPen.setCosmetic(true); // Suaviza as bordas da linha

    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect();
    shadowEffect->setColor(QColor(0, 0, 0, 100)); // Cor e transparência da sombra
    shadowEffect->setBlurRadius(4); // Raio do efeito de sombreamento
    shadowEffect->setOffset(2); // Deslocamento da sombra em relação à linha
    this->setGraphicsEffect(shadowEffect);

    this->setPen(linkPen);

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

void Link::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsPolygonItem::paint(painter, option, widget);

    QLineF line(getMiddleOfIcon(begin), getMiddleOfIcon(end));
    QLineF norm = line.normalVector().unitVector();

    qreal arrowSize = 5;
    qreal angle = std::atan2(-norm.dy(), norm.dx());
    QPointF arrowP1 = line.p2() - QPointF(sin(angle - M_PI / 3) * arrowSize, cos(angle - M_PI / 3) * arrowSize);
    QPointF arrowP2 = line.p2() - QPointF(sin(angle + M_PI / 3) * arrowSize, cos(angle + M_PI / 3) * arrowSize);

    painter->setBrush(QColor(9, 132, 227));
    painter->drawPolygon(QPolygonF() << line.p2() << arrowP1 << arrowP2);
}

void Link::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    select(); // Call the select function to toggle the color
    QGraphicsPolygonItem::mousePressEvent(event);
}

void Link::select() {
    if (begin->isSelected == false) {
        begin->isSelected = true;
        end->isSelected = true;
        linkPen.setColor(QColor(9, 132, 227));
        this->setPen(linkPen);
    } else {
        begin->isSelected = false;
        end->isSelected = false;
        linkPen.setColor(QColor(245, 69, 55));
        this->setPen(linkPen);
    }
}

std::string *Link::getName() {
    return name;
}
