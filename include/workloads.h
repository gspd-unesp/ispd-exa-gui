#ifndef WORKLOADS_H
#define WORKLOADS_H

#include <QMainWindow>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui
{
class Workloads;
}
QT_END_NAMESPACE

class Workloads : public QMainWindow
{
    Q_OBJECT

  public:
    Workloads(QWidget *parent = nullptr);
    ~Workloads();

  private slots:
    void on_pushButton_clicked();

  private:
    Ui::Workloads *ui;
};

#endif
