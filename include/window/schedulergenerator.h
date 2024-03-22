#ifndef SCHEDULERGENERATOR_H
#define SCHEDULERGENERATOR_H

#include <QMainWindow>

namespace Ui {
class SchedulerGenerator;
}

class SchedulerGenerator : public QMainWindow
{
    Q_OBJECT

public:
    explicit SchedulerGenerator(QWidget *parent = nullptr);
    ~SchedulerGenerator();

private slots:

    void on_stackedWidget_currentChanged(int arg1);

    void on_firstOkBtn_clicked();

    void on_secondOkBtn_clicked();

    void on_firstBackBtn_clicked();

    void on_incRdn_toggled(bool checked);

    void on_decRdn_toggled(bool checked);

    void on_randomRdn_toggled(bool checked);

    void on_fifoRdn_toggled(bool checked);


    void on_eraseBtn_clicked();

    void on_secondBackBtn_clicked();

    void on_thirdOkBtn_clicked();

    void on_thirdBackbtn_clicked();

    void on_lastOkBtn_clicked();

    void on_finishBtn_clicked();

private:
    Ui::SchedulerGenerator *ui;
    QString scheduler_name;
    QString scheduler_type;
    QString formula;
    QString restriction;

    void change_page(bool backwards);
    void disable_bold();
    void disable_variables(bool disable);
    void disable_operands(bool disable);
    void append_variable(QString variable);
    void append_operands(QString operand);
};

#endif // SCHEDULERGENERATOR_H
