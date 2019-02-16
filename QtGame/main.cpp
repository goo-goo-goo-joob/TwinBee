#include <QCoreApplication>
#include <iostream>
#include <QSettings>
#include <QVariant>
#include <QString>
#include "Game.h"
#include "mainwindow.h"
#include <QApplication>
#include "Initialization.h"
class QPaintEvent;
using namespace std;


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    Initialization& ini = Initialization::Instance();
    ini.Init("settings.ini");
    Game& game = Game::Instance();

    MainWindow w;
    w.show();

    //game.Draw();
    cout << game.width() << game.height();
    ini.Save("setgame", "level", 2);
    ini.Save("setgame", "score", 100);
    ini.Save("logs", "no logs", 1);
    return a.exec();
}
