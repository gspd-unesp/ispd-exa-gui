#ifndef MACHINECONFIGURATION_H
#define MACHINECONFIGURATION_H

#include <QPlainTextEdit>
#include <QSettings>
#include <QDialog>

namespace Ui {
class machineIconConfiguration;
}

class machineIconConfiguration : public QDialog
{
    Q_OBJECT

public:
    explicit machineIconConfiguration(const QString &iconName, QWidget *parent = nullptr);
    ~machineIconConfiguration();

    // Adicione funções para obter e configurar os valores dos widgets da janela
    QString getLineEditValue();
    void setLineEditValue(const QString& value);

    int getComboBoxIndex();
    void setComboBoxIndex(int index);

    bool getCheckBoxState();
    void setCheckBoxState(bool checked);

private:
    Ui::machineIconConfiguration *ui;
signals:
    void configurationClicked();

};

#endif // MACHINECONFIGURATION_H
