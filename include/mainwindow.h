#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "userwindow.h"
#include "workloads.h"
#include "ui_mainwindow.h"

#include <QGraphicsScene>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QVBoxLayout>

#include <gridscene.h>


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
    GridScene      *scene;
    QImage         *headp;
    QImage         *headc;

    UserWindow *userWindow;
    Workloads  *workloadsWindow;

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
