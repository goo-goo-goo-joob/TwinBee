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
    }
    void access(Visitor &v) override {
        v.visit(*this);
      }
};
