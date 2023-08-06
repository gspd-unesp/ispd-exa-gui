#ifndef SIMULATION_H
#define SIMULATION_H

#include <QWidget>
#include <QDir>


namespace Ui {
class Simulation;
}

class Simulation : public QWidget
{
    Q_OBJECT

public:
    explicit Simulation(QWidget *parent = nullptr);
    bool eventFilter(QObject *obj, QEvent *event) override;
    ~Simulation();

private slots:
    void on_pushButton_clicked();

private:
    void createGlobal(QDir directory);
    void createTasks(QDir directory);
    void createUser(QDir directory);
    void createResources(QDir directory);
    void createResultsFile(QDir directory);
    void resultsCommunication(QDir directory);
    void resultsProcessing(QDir directory);
    void circlePacking(int flag,QDir directory);

    void createStackedLineGraph(QDir directory);


    QPoint originalTextEditPos;
    QSize originalTextEditSize;
    QPoint originalLabelPos;
    QSize originalLabelSize;
    Ui::Simulation *ui;
};

#endif // SIMULATION_H
