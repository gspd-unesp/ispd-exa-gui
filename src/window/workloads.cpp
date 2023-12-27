#include "window/workloads.h"
#include "components/conf/itemconfiguration.h"
#include "context/workload.h"
#include <QAbstractTableModel>
#include <qabstractitemmodel.h>
#include <qboxlayout.h>
#include <qheaderview.h>
#include <ui_workloads.h>

struct WorkloadModel : QAbstractTableModel
{
public:
    WorkloadModel(){};

    void setWorkloads(std::vector<Context::Workload> *workloads)
    {
        this->beginResetModel();
        this->workloads = workloads;
        this->endResetModel();
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override
    {
        return parent.isValid() ? 0 : this->workloads->size();
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override
    {
        return parent.isValid() ? 0 : 10; // Number of attributes in Workloads
    }

    QVariant headerData(int             section,
                        Qt::Orientation orientation,
                        int             role) const override
    {
        if (role != Qt::DisplayRole)
            return QVariant();

        if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0:
                return "Master";
            case 1:
                return "Owner";
            case 2:
                return "Type";
            case 3:
                return "Min Communication";
            case 4:
                return "Max Communication";
            case 5:
                return "Min Processment";
            case 6:
                return "Max Processment";
            case 7:
                return "Remaining Tasks";
            case 8:
                return "Arrival Type";
            case 9:
                return "Arrival Lambda";
            default:
                return QVariant();
            }
        }
        return QVariant();
    }

    QVariant data(const QModelIndex &index,
                  int                role = Qt::DisplayRole) const override
    {
        if (!index.isValid() || role != Qt::DisplayRole)
            return QVariant();

        Context::Workload &workload = workloads->at(index.row());
        switch (index.column()) {
        case 0: // Master name
            return QString::fromStdString(
                workload.master->getConf()->getName());
        case 1: // User name
            return QString::fromStdString(workload.owner->name);
        case 2: // Type of the workload
            return workload.getTypeString();
        case 3: // Minimal Communication Size
            return workload.minCommSize;
        case 4: // Max Communication Size
            return workload.maxCommSize;
        case 5: // Minimal Processment Size
            return workload.minProcSize;
        case 6: // Max Processment Size
            return workload.maxProcSize;
        case 7: // Remaining Tasks
            return workload.remainingTasks;
        case 8: // Type of the arrival
            return workload.arrivalType.getTypeString();
        case 9: // Lambda of the arrival
            return workload.arrivalType.lambda;

        default:
            return QVariant();
        }
    };

private:
    std::vector<Context::Workload> *workloads;
};

WorkloadsWindow::WorkloadsWindow(std::vector<Context::Workload> *workloads,
                                 QWidget                        *parent)
    : QDialog(parent), workloads{workloads}
{
    auto mainLayout = new QVBoxLayout(this);

    auto tableModel = new WorkloadModel();
    tableModel->setWorkloads(this->workloads);

    this->workloadTable->setModel(tableModel);

    mainLayout->addWidget(this->workloadTable);
}

void WorkloadsWindow::on_pushButton_clicked()
{
    QTextStream message(stdout);
    message << "Program will be closed" << Qt::endl;

    QApplication::quit();
}
