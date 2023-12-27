#pragma once

#include "context/workload.h"
#include <QDialog>
#include <QTextStream>
#include <QTableView>
#include <vector>

class WorkloadsWindow : public QDialog
{
    Q_OBJECT

public:
    WorkloadsWindow(std::vector<Context::Workload> *workloads, QWidget *parent = nullptr);

private:
    QTableView *workloadTable = new QTableView(this);
    std::vector<Context::Workload> *workloads;

private slots:
    void                            on_pushButton_clicked();

};
