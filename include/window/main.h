#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "window/users.h"
#include "window/workloads.h"
#include "drawingtable/scene.h"
#include "ui_mainwindow.h"

#include <QGraphicsScene>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QVBoxLayout>

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

private:
    Ui::MainWindow *ui;
    Scene      *scene;
    QImage         *headp;
    QImage         *headc;

    UserWindow *userWindow;
    WorkloadsWindow  *workloadsWindow;

    QImage *bPcIcon;
    QImage *bNoneIcon;
    QImage *bClusterIcon;
    QImage *buttonBicon;
    QImage *buttonCicon;
signals:
private slots:
    void on_buttonB_clicked();
    void on_buttonC_clicked();
    void on_bPc_clicked();
    void on_bCluster_clicked();
    void on_bLink_clicked();
    void on_bNone_clicked();
};

#endif // MAINWINDOW_H
