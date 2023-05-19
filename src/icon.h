#ifndef ICON_H
#define ICON_H

#include <QObject>
#include <QGraphicsItem>
#include <QObject>
#include <string>

class Icon : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Icon(const char *name, QGraphicsItem *parent = nullptr);
    Icon(QPixmap pixmap, QGraphicsItem *parent = nullptr);
    // static Icon *fromPath(const char *name, QGraphicsItem *parent = nullptr);

    const char *iconPath;

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QString         positionString;
    // Ui::MainWindow *ui;
    std::string    *name;

signals:
};

#endif // ICON_H
