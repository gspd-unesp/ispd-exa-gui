#pragma once
#include <QDialog>
#include <QPlainTextEdit>
#include <QSettings>

class SwitchConfiguration;

namespace Ui
{
class SwitchConfigurationWindow;
}

class SwitchConfigurationWindow : public QDialog
{
    Q_OBJECT

public slots:
    void setName(const QString &newName);
    void setBandwidth(int newBandwidth);
    void setLoadFactor(const double newLoadFactor);
    void setLatency(const double newLatency);

public:
    explicit SwitchConfigurationWindow(SwitchConfiguration *conf,
                                     QWidget           *parent = nullptr);

private:
    void setupConfAndWindow();
    Ui::SwitchConfigurationWindow *ui;
    SwitchConfiguration           *conf;
};
