#ifndef MACHINECONFIGURATION_H
#define MACHINECONFIGURATION_H

#include <QPlainTextEdit>
#include <QSettings>
#include <QDialog>

class MachineConfiguration;

namespace Ui {
class MachineConfigurationWindow;
}

class MachineConfigurationWindow : public QDialog
{
    Q_OBJECT

public slots:
    void setName(const QString &newName);
    void setCoreCount(const int coreCount);
    void setComputationPower(const int computationPower);
    void setLoadFactor(const double loadFactor);
    void setGpuCoreCount(const int coreCount);
    void setGpuPower(const int gpuPower);
    void setGpuBandwidth(const int gpuBandwidth);
    void setRam(const int ram);
    void setDisk(const int disk);
    void setWattageIdle(const int wattageIdle);
    void setWattageMax(const int wattageMax);
    void checkMaster(const int checked);
    void setScheduler(const QString);

public:
    explicit MachineConfigurationWindow(MachineConfiguration *conf, QWidget *parent = nullptr);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MachineConfigurationWindow *ui;
    MachineConfiguration *conf;
    void setupConfAndWindow();
};

#endif // MACHINECONFIGURATION_H
