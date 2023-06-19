#ifndef ICON_H
#define ICON_H

#include <QVector>
#include <QLabel>
#include <QGraphicsItem>
#include <QObject>
#include <string>

class Link;

class Icon : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Icon(const char *name, QGraphicsItem *parent = nullptr);
    Icon(QPixmap pixmap, QGraphicsItem *parent = nullptr);
    void setOutputLabel(QLabel *label);
    QVector<Link *> *links;
    std::string *getName();
    bool isSelected;

    const char *iconPath;
    const char *iconPathSelected;

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    void updatePosition();
    QString positionString;
    QLabel  *outputLabel;
    std::string *name;
signals:
};

#endif
