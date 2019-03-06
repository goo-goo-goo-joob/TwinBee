#include <QCoreApplication>
#include <iostream>
#include <QSettings>
#include <QVariant>
#include <QString>
#include "Game.h"
#include "mainwindow.h"
#include <QApplication>
#include "Initialization.h"
#include <ctime>

class QPaintEvent;
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    srand((unsigned int)time(NULL));//helps to generate random coords of objects
    Initialization& ini = Initialization::Instance();
    ini.Init("settings.ini");
    Game& game = Game::Instance();
    MainWindow w;
//    w.setStyleSheet("background-image: url(images/Bee.png); "
//                                "background-position: top left; "
//                                "background-repeat: repeat-xy;");
    w.show();
    return a.exec();
}
