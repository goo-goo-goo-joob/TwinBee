#ifndef INITIALIZATION_H
#define INITIALIZATION_H
#include <QCoreApplication>
#include <QSettings>
#include <QString>
#include "Game.h"
#include "Cloud.h"

class Initialization
{
    QString _path;
    Initialization(){

    }
    ~Initialization(){}

public:
    static Initialization& Instance()
    {
        static Initialization i;
        return i;
    }
    void Init(QString p)
    {
        _path = QCoreApplication:: applicationDirPath();
        _path.append(p);
        QSettings sett(_path, QSettings::IniFormat);
        //Cloud::SetDafaultParams(sett);
        Game::Instance().SetDafaultParams(sett);

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
    int setScoreRed(){
        QSettings sett(_path, QSettings::IniFormat);
        return sett.value("setscore/RedEnemy", 0).toInt();
    }

};

#endif // INITIALIZATION_H
