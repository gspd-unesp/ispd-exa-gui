#include "window/main.h"
#include <window/simulation.h>

#include <QApplication>
#include <QScreen>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    MainWindow mw;

    mw.setWindowTitle("iSPD");

//    int width = 800;
//    int height = 600;

//    QScreen *primaryScreen = QGuiApplication::primaryScreen();

//    QRect screenGeometry = primaryScreen->geometry();

//    int x = (screenGeometry.width() - width) / 2;
//    int y = (screenGeometry.height() - height) / 2;

//    // Define a posição central da janela
//    mw.move(x, y);

//    // Define o tamanho da janela
//    mw.resize(width, height);


    mw.show();

    return app.exec();
}
