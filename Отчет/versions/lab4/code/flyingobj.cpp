#include "flyingobj.h"
#include "Game.h"

FlyingObj::FlyingObj(){
    Initialization& ini = Initialization::Instance();
    Game& game = Game::Instance();
    _speed = ini.Sett("setspeed/FlyingObj");
    if (_speed < 0){
        _speed = 0;
    }
    _x = game.bee->X() + game.bee->SizeX()/2 - 5;
    _y = game.bee->Y() - game.bee->SizeY()/2;
    Notifer::Instance().Subscribe(this);
}

FlyingObj::~FlyingObj(){
    Notifer::Instance().Unsubscribe(this);
}

void FlyingObj::Update(const Notifer &n){
    Move();
}
