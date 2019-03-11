#pragma once
#include "GameItem.h"
#include "initialization.h"

class Bee :
    public GameItem
{
    int _lifes;
    int lastShoot;
    int lifeTime;
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
        _lifes = ini.Sett("setgame/lifes");
        if (_lifes < 0){
            _lifes = 0;
        }
        sizeX = 60;
        sizeY = 53;
        right= false;
        left= false;
        up= false;
        down= false;
        lastShoot = -1;
        lifeTime = 20;
    }
    ~Bee(){}
    void access(Visitor &v) override {
        v.visit(*this);
      }
    void Move();
    void Update(const Notifer& n) override {
        if(n.getStage() - lastShoot >= lifeTime){
            lastShoot = n.getStage();
            SubLifes();
        }
    }
    void SubLifes();
    int Lifes() {return _lifes;}
    void Lifes(int lifes){_lifes = lifes;}
};
