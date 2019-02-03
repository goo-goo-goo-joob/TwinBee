#include <QCoreApplication>
#include <iostream>
#include "Game.h"
#include <QSettings>
#include <QVariant>
#include <QString>


using namespace std;
class Initialization
{


};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSettings sett("C:\\Users\\Pro18\\Projects\\QtGame\\settings.ini", QSettings::IniFormat);
    int val = sett.value("setgame/level", 0).toInt();
    cout << val << endl;

    Game& game = Game::Instance(); //безопасный способ получения ссылки на Singleton
    game.Draw();
    return a.exec();
}
