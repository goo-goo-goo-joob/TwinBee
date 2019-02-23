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
        //_notifer->Subscribe(this);
    }
    ~Bee(){
        //_notifer->Unsubscribe(this);
    }
    void access(Visitor &v) override {
        v.visit(*this);
      }
    void Move(int x){
        _x += x;
    }
    bool Update(Notifer* n) override{}
    //bool Update(Notifer* n) override{
    //    if(n == _notifer)
    //        Move();
    //}
};
