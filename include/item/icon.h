#ifndef ICON_H
#define ICON_H

#include "qgraphicsscene.h"
#include <QGraphicsItem>
#include <QLabel>
#include <QObject>
#include <QVector>
#include <map>
#include <string>

class Link;

class Icon : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Icon(const char *name, QGraphicsItem *parent = nullptr);
    ~Icon();
    Icon(QPixmap pixmap, QGraphicsItem *parent = nullptr);
    void             setOutputLabel(QLabel *label);
    std::map<unsigned, Link *> *links;
    std::string     *getName();
    bool             isSelected;
    unsigned         id;

    std::string iconPath;
    std::string iconPathSelected;

    void deselect();
protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private:
    void         updatePosition();
    void         select();
    QString      positionString;
    QLabel      *outputLabel;
    std::string *name;
signals:
};

#endif
