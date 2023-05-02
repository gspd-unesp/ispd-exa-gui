#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "userwindow.h"
#include "workloads.h"
#include "griditem.h"

#include <QGraphicsScene>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QVBoxLayout>

#include <src/gridscene.h>

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
    GridScene *scene;
    QImage *headp;
    QImage *headc;
    GridItem *current_item;

    UserWindow *userWindow;
    Workloads *workloadsWindow;

    QImage *buttonPCIcon;
    QImage *buttonClusterIcon;
    QImage *buttonBicon;
    QImage *buttonCicon;
  signals:
  private slots:
    void on_buttonPC_clicked();
    void on_buttonCluster_clicked();
    void on_buttonB_clicked();
    void on_buttonC_clicked();

};

#endif // MAINWINDOW_H
