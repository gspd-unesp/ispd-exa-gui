#ifndef USERWINDOW_H
#define USERWINDOW_H
#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include "window/adduser.h"
#include "ui_userwindow.h"

namespace Ui
{
class UserWindow;
} // namespace Ui

class UserWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserWindow(QWidget *parent = nullptr);
    void addOnList1(const QString &valor);
    void addOnList2(double valor);

    ~UserWindow();

private:
    Ui::UserWindow *ui;
    QListWidget *listWidget;
    QListWidget *listWidget_2;
    addUser *adduser;
    QImage *fecharImg;
    QImage *addIcon;
    QStringList list1Values;
    QStringList list2Values;
    int mnSelected = -1;

private slots:
    void on_addButton_clicked();
    void on_pushButton_clicked();
    void on_listWidget_currentRowChanged(int currentRow);
    void on_listWidget_2_currentRowChanged(int currentRow);
    void on_okButton_clicked();
    void clearListWidgets();


signals:
    void itemMoved(const QPointF &pos);
};
#endif // USERWINDOW_H



