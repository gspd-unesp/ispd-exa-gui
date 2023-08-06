#ifndef MACHINECONFIGURATION_H
#define MACHINECONFIGURATION_H

#include <QPlainTextEdit>
#include <QSettings>
#include <QDialog>
#include "window/users.h"


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
    QString getLineEdit01Value();
    QString getLineEdit02Value();
    QString getLineEdit03Value();
    QString getLineEdit04Value();
    QString getLineEdit05Value();
    QString getLineEdit06Value();
    QString getLineEdit07Value();
    QString getLineEdit08Value();

    void setLineEdit01Value(const QString& value);
    void setLineEdit02Value(const QString& value);
    void setLineEdit03Value(const QString& value);
    void setLineEdit04Value(const QString& value);
    void setLineEdit05Value(const QString& value);
    void setLineEdit06Value(const QString& value);
    void setLineEdit07Value(const QString& value);
    void setLineEdit08Value(const QString& value);

    int getOwnerComboBoxIndex();
    void setOwnerComboBoxIndex(int indexowner);

    int getSchedulingComboBoxIndex();
    void setSchedulingComboBoxIndex(int indexschedule);

    bool getCheckBoxState();
    void setCheckBoxState(bool checked);

    void addUsersToOwnerComboBox(const QList<QString> &list1Data);
private:
    Ui::machineIconConfiguration *ui;
signals:
    void configurationClicked();

};

#endif // MACHINECONFIGURATION_H
