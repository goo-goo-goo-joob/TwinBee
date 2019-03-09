#include "Bee.h"
#include "Game.h"

void Bee::Move(){
    Game& game = Game::Instance();
    if (left && _x - _speed >= 0){
        _x -= _speed;
    }
    if (right && _x + sizeX + _speed <= game.width()) {
        _x += _speed;
    }
    if (up && _y - _speed >= 0) {
        _y -= _speed;
    }
    if (down && _y + sizeY /*+ _speed*/ <= game.height()) {
        _y += _speed;
    }
}

void Bee::SubLifes() {
    if(_lifes > 1)
        _lifes--;
    else{
       _lifes = 0;
       Game& game = Game::Instance();
       game.play(false);
    }
}
