#ifndef USERWINDOW_H
#define USERWINDOW_H
#include <QMainWindow>

namespace Ui {
class UserWindow;
} // namespace Ui

class UserWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit UserWindow(QWidget *parent = nullptr);
  ~UserWindow();

private:
  Ui::UserWindow *ui;
};
#endif // USERWINDOW_H
