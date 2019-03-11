#include "bell.h"
#include "Game.h"

Bell::Bell(int x, int y){
    Initialization& ini = Initialization::Instance();
    Game& game = Game::Instance();
    _speed = ini.Sett("setspeed/Bell");
    if (_speed < 0){
        _speed = 0;
    }
    _score = ini.Sett("setscore/Bell");
    if (_score < 0){
        _score = 0;
    }
    _x0 = _x = x;
    _y0 = _y = y;
    sizeX = 30;
    sizeY = 33;
    Notifer::Instance().Subscribe(this);
    start = Notifer::Instance().getStage();
    moveType = 0;
}

bool Bell::isIn() {
    Game& game = Game::Instance();
    return (0 < _x && _x < game.width() && game.height() > _y);
}
