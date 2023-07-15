#ifndef MACHINECONFIGURATION_H
#define MACHINECONFIGURATION_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QSettings>


namespace Ui {
class machineIconConfiguration;
}

class machineIconConfiguration : public QWidget
{
    Q_OBJECT

public:
    explicit machineIconConfiguration(const QString &iconName, QWidget *parent = nullptr);
    ~machineIconConfiguration();


private:
    Ui::machineIconConfiguration *ui;
};

#endif // MACHINECONFIGURATION_H
