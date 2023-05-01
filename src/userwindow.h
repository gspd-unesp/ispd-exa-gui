#ifndef USERWINDOW_H
#define USERWINDOW_H
#include <QMainWindow>
#include "settingswindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace Ui
{
class UserWindow;
} // namespace Ui

class UserWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit UserWindow(QWidget *parent = nullptr);
    ~UserWindow();

  private:
    Ui::UserWindow *ui;
    QImage *fecharImg;
    QImage *addIcon;
    SettingsWindow *settingswindow;
  private slots:
    void on_addButton_clicked();
  signals:
    void itemMoved(const QPointF &pos);
};
#endif // USERWINDOW_H
