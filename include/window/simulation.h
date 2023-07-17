#ifndef SIMULATION_H
#define SIMULATION_H

#include <QWidget>

namespace Ui {
class Simulation;
}

class Simulation : public QWidget
{
    Q_OBJECT

public:
    explicit Simulation(QWidget *parent = nullptr);
    ~Simulation();

private slots:
    void on_pushButton_clicked();

private:
    void createGlobal();
    void createTasks();
    void createUser();
    void createResources();
    void createResultsFile();
    void resultsCommunication();
    void resultsProcessing();
    void circlePacking(int flag);
    Ui::Simulation *ui;
};

#endif // SIMULATION_H
