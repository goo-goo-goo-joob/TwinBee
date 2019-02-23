#pragma once
#include "GameItem.h"
#include "initialization.h"

//class visitor
class FlyingObj :
    public GameItem
{
    int _speed;
public:
    FlyingObj(int x, int y){
        Initialization& ini = Initialization::Instance();
        _speed = ini.Sett("setspeed/FlyingObj");
        if (_speed < 0){
            _speed = 0;
        }
        _x = x;
        _y = y;
    }
    void access(Visitor &v) override {
        v.visit(*this);
    }
};
