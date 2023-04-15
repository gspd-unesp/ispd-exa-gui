#include "mainwindow.h"

#include <QApplication>

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  MainWindow mw;

  mw.setWindowTitle("iSPD");
  mw.show();

  return app.exec();
}

//#include <QGraphicsItem>
//#include <QGraphicsView>
//#include <QApplication>
//#include <QtGui>

//class CustomView : public QGraphicsView
//{
//protected:
//    void mousePressEvent(QMouseEvent *event)
//    {
//        qDebug() << "Custom view clicked.";
//        QGraphicsView::mousePressEvent(event);
//    }
//};

//class CustomItem : public QGraphicsRectItem
//{
//protected:
//    void mousePressEvent(QGraphicsSceneMouseEvent *event)
//    {
//        qDebug() << "Custom item clicked.";
//    }
//};

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);

//    CustomItem item;
//    item.setRect(20, 20, 60, 60);

//    QGraphicsScene scene(0, 0, 100, 100);
//    scene.addItem(&item);

//    CustomView view;
//    view.setScene(&scene);
//    view.show();
//    return a.exec();
//}
