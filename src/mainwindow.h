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
    QImage *head;
    GridItem *current_item;

    UserWindow *userWindow;
    Workloads *workloadsWindow;
  signals:
  private slots:
    void on_button_b_clicked();
    void on_button_c_clicked();
    void on_buttonA_clicked();
    void updateposition();
};

#endif // MAINWINDOW_H
