#ifndef RUN_SIMULATION_WINDOW_H
#define RUN_SIMULATION_WINDOW_H

#include <QDialog>

namespace Ui {
class run_simulation_window;
}

class run_simulation_window : public QDialog
{
    Q_OBJECT

public:
    explicit run_simulation_window(QWidget *parent = nullptr);
    ~run_simulation_window();

private slots:
    void on_rossbuilderBtn_clicked();

    void on_modelBtn_clicked();

    void on_routesBtn_clicked();

    void on_okBtn_clicked();


private:
    Ui::run_simulation_window *ui;
};

#endif // RUN_SIMULATION_WINDOW_H
