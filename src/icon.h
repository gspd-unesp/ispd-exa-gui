#ifndef ICON_H
#define ICON_H

#include <QLabel>
#include <QGraphicsItem>
#include <QObject>
#include <string>

class Icon : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Icon(const char *name, QGraphicsItem *parent = nullptr);
    Icon(QPixmap pixmap, QGraphicsItem *parent = nullptr);
    void setOutputLabel(QLabel *label);

    const char *iconPath;

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    void updatePosition();
    QString positionString;
    QLabel  *outputLabel;
    // Ui::MainWindow *ui;
    std::string *name;

signals:
};

#endif // ICON_H
