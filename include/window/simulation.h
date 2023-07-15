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

private:
    Ui::Simulation *ui;
};

#endif // SIMULATION_H
