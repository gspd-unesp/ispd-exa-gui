#ifndef USERWINDOW_H
#define USERWINDOW_H
#include "context/context.h"
#include <QComboBox>
#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QList>
#include <QListWidget>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QWidget>
#include <qtablewidget.h>
#include <ui_userwindow.h>
class DrawingTable;

class UserWindow : public QWidget
{
    Q_OBJECT

public:
    UserWindow(Context::MainContext *context, QWidget *parent = nullptr);

protected:
private:
    void                  onItemChanged(QTableWidgetItem *item);
    QTableWidget          usersTable;
    Context::MainContext *context;
    void                  insertUsers();

    QPushButton *addUserB    = new QPushButton("Add");
    QPushButton *deleteUserB = new QPushButton("Del");

private slots:
    void addUser();

signals:
};
#endif // USERWINDOW_H
