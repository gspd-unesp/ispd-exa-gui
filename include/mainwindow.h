#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "userwindow.h"
#include "workloads.h"

#include <QGraphicsScene>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QVBoxLayout>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  explicit MainWindow(QWidget *parent = nullptr);

private:
  Ui::MainWindow *ui;
  QGraphicsScene *scene;
  QImage *head;
  QGraphicsPixmapItem *item;

  UserWindow *userWindow;
  Workloads *workloadsWindow;
signals:
private slots:
  void on_button_a_clicked();
  void on_button_b_clicked();
  void on_button_c_clicked();
};

#endif // MAINWINDOW_H
