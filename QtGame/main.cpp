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
    Game& game = Game::Instance(); //безопасный способ получения ссылки на Singleton
    game.Draw();
    return a.exec();
}
