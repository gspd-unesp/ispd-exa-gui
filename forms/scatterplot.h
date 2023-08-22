#ifndef SCATTERPLOT_H
#define SCATTERPLOT_H

#include <QWidget>
#include <QDir>

namespace Ui {
class scatterPlot;
}

class scatterPlot : public QWidget
{
    Q_OBJECT

public:
    explicit scatterPlot(QWidget *parent = nullptr);
    ~scatterPlot();

private:
    Ui::scatterPlot *ui;
    void createScatterPlot(QDir directory);
};

#endif // SCATTERPLOT_H
