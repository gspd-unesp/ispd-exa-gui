#include "../include/mainwindow.h"

#include <QApplication>

int main(int argc, char **argv) {
  QApplication::setStyle("motif");
  QApplication app(argc, argv);

  MainWindow mw;

  mw.setWindowTitle("iSPD");
  mw.show();

  return app.exec();
}
