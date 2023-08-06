#ifndef USERWINDOW_H
#define USERWINDOW_H
#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include "window/adduser.h"
#include "ui_userwindow.h"
#include <QList>
#include <QGraphicsItem>
#include <QWidget>
#include <QComboBox>
#include <QDebug>
#include <string>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
// #include "item/icon.h"

// #include "drawingtable/drawingtable.h"
class Icon;
class DrawingTable;

namespace Ui
{
class UserWindow;
} // namespace Ui

class UserWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserWindow(QWidget *parent = nullptr, DrawingTable* drawingTable = nullptr, const QList<QString> &list1Data = QList<QString>(), const QList<double> &list2Data = QList<double>(), const QList<Icon*> &icons = QList<Icon*>());
    void addOnList1(const QString &valor);
    void addOnList2(double valor);
    void setDrawingTable(DrawingTable* drawingTable);
    void receiveUserWindowData(const QList<QString> &list1Data, const QList<double> &list2Data);
    ~UserWindow();

protected:

private:
    Ui::UserWindow *ui;
    QListWidget *listWidget;
    QListWidget *listWidget_2;
    addUser *adduser;
    QImage *fecharImg;
    QImage *addIcon;
    QStringList list1Values;
    QStringList list2Values;
    int mnSelected = -1;
    DrawingTable* drawingTable;
    QList<Icon*> icons;

private slots:
    void on_addButton_clicked();
    void on_pushButton_clicked();
    void on_listWidget_currentRowChanged(int currentRow);
    void on_listWidget_2_currentRowChanged(int currentRow);
    void on_okButton_clicked();
    void clearListWidgets();


signals:
    void itemMoved(const QPointF &pos);
};
#endif // USERWINDOW_H



