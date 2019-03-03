#pragma once
#include "GameItem.h"
#include "initialization.h"

class Cloud :
	public GameItem
{
    int _speed;
public:
    Cloud(){
        Initialization& ini = Initialization::Instance();
        _speed = ini.Sett("setspeed/Cloud");
        if (_speed < 0){
            _speed = 0;
        }
        int x = ini.Sett("setgame/width", 900);
        if (x < 0){
            x = 900;
        }
        x -= 50;
        int y = ini.Sett("setgame/height", 700);
        if (y < 0){
            y = 700;
        }
        y /= 2;
         _x = rand()%x;
         _y = rand()%y;
    }
    void access(Visitor &v) override {
        v.visit(*this);
      }
};


