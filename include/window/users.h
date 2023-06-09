#ifndef USERWINDOW_H
#define USERWINDOW_H
#include <QMainWindow>
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
  signals:
    void itemMoved(const QPointF &pos);
};
#endif // USERWINDOW_H
