#pragma once
#include "GameItem.h"
#include "initialization.h"

class Bee :
	public GameItem
{
public:
    Bee(){
        Initialization& ini = Initialization::Instance();
        _x = ini.Sett("setcoord/bee_x");
        if (_x < 0){
            _x = 0;
        }
        _y = ini.Sett("setcoord/bee_y");
        if (_y < 0){
            _y = 0;
        }
        _speed = ini.Sett("setspeed/Bee");
        if (_speed < 0){
            _speed = 0;
        }
    }
    void access(Visitor &v) override {
        v.visit(*this);
      }
    void Move(int x){
        _x += x;
    }
};
