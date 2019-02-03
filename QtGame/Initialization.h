#ifndef INITIALIZATION_H
#define INITIALIZATION_H
#include <QCoreApplication>
#include <QSettings>
#include <QString>
#include "Game.h"

class Initialization
{
    QString _path;
public:
    Initialization(QString p){
        _path = QCoreApplication:: applicationDirPath();
        _path.append(p);
        QSettings sett(_path, QSettings::IniFormat);
        Game& game = Game::Instance(); //безопасный способ получения ссылки на Singleton
        game.level(Level(sett.value("setgame/level", 0).toInt()));
        game.play(true);
        game.width(sett.value("setgame/wigth", 900).toInt());
        game.height(sett.value("setgame/height", 700).toInt());
        game.score(sett.value("setgame/score", 0).toInt());

    }
    void Save(){
        QSettings sett(_path, QSettings::IniFormat);
        Game& game = Game::Instance();
        sett.setValue("setgame/level", int(game.level()));
        sett.setValue("setgame/play", int(game.play()));
        sett.setValue("setgame/width", game.width());
        sett.setValue("setgame/height", game.height());
        sett.setValue("setgame/score", game.score());
    }
    ~Initialization() {}
};

#endif // INITIALIZATION_H
