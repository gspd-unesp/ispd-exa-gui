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

public:
    explicit MachineConfigurationWindow(MachineConfiguration *conf, QWidget *parent = nullptr);

private:
    Ui::MachineConfigurationWindow *ui;
    MachineConfiguration *conf;
};

#endif // MACHINECONFIGURATION_H
