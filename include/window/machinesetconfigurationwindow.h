#pragma once
#include <QDialog>
#include <QPlainTextEdit>
#include <QSettings>

class MachineSetConfiguration;

namespace Ui
{
class MachineSetConfigurationWindow;
}

class MachineSetConfigurationWindow : public QDialog
{
    Q_OBJECT

public slots:
    void setName(const QString &newName);
    void setBandwidth(int newBandwidth);
    void setLoadFactor(const double newLoadFactor);
    void setLatency(const double newLatency);

public:
    explicit MachineSetConfigurationWindow(MachineSetConfiguration *conf,
                                     QWidget           *parent = nullptr);

private:
    Ui::MachineSetConfigurationWindow *ui;
    MachineSetConfiguration           *conf;
};
