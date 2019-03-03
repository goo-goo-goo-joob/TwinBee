#pragma once
#include "GameItem.h"
#include "initialization.h"

class Bee :
    public GameItem
{
private:
    int sizeX;
    int sizeY;
public:
    bool right, left, up, down;
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
        sizeX = 25;
        sizeY = 25;
        right= false;
        left= false;
        up= false;
        down= false;
        //_notifer->Subscribe(this);
    }
    int SizeX(){
        return sizeX;
    }
    int SizeY(){
        return sizeY;
    }
    ~Bee(){
        //_notifer->Unsubscribe(this);
    }
    void access(Visitor &v) override {
        v.visit(*this);
      }
    void Move();
    void Update(const Notifer& n) override {}
};
