#ifndef ADDUSER_H
#define ADDUSER_H
#include <QWidget>
#include <QLineEdit>
namespace Ui {
class addUser;
}

class addUser : public QWidget
{
    Q_OBJECT

public:
    explicit addUser(QWidget *parent = nullptr);
    QString getText();
    QString getText2();
    ~addUser();

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();

private:
    QLineEdit *lineEdit1;
    QLineEdit *lineEdit2;
    Ui::addUser *ui;
};

#endif // ADDUSER_H
