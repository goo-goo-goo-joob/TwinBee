#include <QCoreApplication>
#include <iostream>
#include <QSettings>
#include <QVariant>
#include <QString>
#include "Game.h"
#include "Initialization.h"

using namespace std;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Initialization& ini = Initialization::Instance();
    ini.Init("settings.ini");
    Game& game = Game::Instance();
    game.Draw();
    cout << game.width() << game.height();
    ini.Save("setgame", "level", 2);
    ini.Save("setgame", "score", 100);
    ini.Save("logs", "no logs", 1);
    return a.exec();
}
