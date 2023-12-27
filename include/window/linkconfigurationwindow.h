#pragma once
#include <QDialog>
#include <QPlainTextEdit>
#include <QSettings>

class LinkConfiguration;

namespace Ui
{
class LinkConfigurationWindow;
}

class LinkConfigurationWindow : public QDialog
{
    Q_OBJECT

public slots:
    void setName(const QString &newName);
    void setBandwidth(int newBandwidth);
    void setLoadFactor(const double newLoadFactor);
    void setLatency(const double newLatency);

public:
    explicit LinkConfigurationWindow(LinkConfiguration *conf,
                                     QWidget           *parent = nullptr);

private:
    void setupConfAndWindow();
    Ui::LinkConfigurationWindow *ui;
    LinkConfiguration           *conf;
};
