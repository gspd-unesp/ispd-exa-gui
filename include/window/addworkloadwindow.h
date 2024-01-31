#ifndef ADDWORKLOADWINDOW_H
#define ADDWORKLOADWINDOW_H

#include <QDialog>
#include <context/context.h>
#include <context/workload.h>
namespace Ui {
class addWorkloadWindow;
}

class addWorkloadWindow : public QDialog
{
    Q_OBJECT

public:
    explicit addWorkloadWindow(QWidget *parent = nullptr,  Context::MainContext *context = nullptr);
    ~addWorkloadWindow();


private slots:
    void on_constantRdn_toggled(bool checked);

    void on_minProcSizeSpin_valueChanged(double arg1);

    void on_minCommSizeSpin_valueChanged(double arg1);

    void on_poisonRdn_toggled(bool checked);

    void on_weibullRdn_toggled(bool checked);

    void on_okBtn_clicked();

    void on_uniformRdn_toggled(bool checked);

    void on_radioButton_toggled(bool checked);

    void on_exponentialRdn_toggled(bool checked);

    void on_fixedRdn_toggled(bool checked);

private:
    Ui::addWorkloadWindow *ui;
    Context::MainContext *context;
    Context::WORKLOAD_TYPE workload_type;
    Context::INTERARRIVAL_TYPE inter_type;

};

#endif // ADDWORKLOADWINDOW_H
