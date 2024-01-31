#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "window/drawingtable/drawingtable.h"
#include "window/drawingtable/scene.h"
#include "ui_mainwindow.h"
#include "window/users.h"

#include <QGraphicsScene>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QVBoxLayout>
#include "context/context.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void show();

protected:
private:
    DrawingTable   *drawingTable;
    std::shared_ptr<Context::MainContext> context;
    Ui::MainWindow *ui;
    Scene          *scene;
    QImage         *headp;
    QImage         *headc;


    UserWindow      *userWindow;

    QImage *bPcIcon;
    QImage *bNoneIcon;
    QImage *bClusterIcon;
    QImage *buttonBicon;
    QImage *buttonCicon;
    QImage *bLinkIcon;
signals:
};

#endif // MAINWINDOW_H
