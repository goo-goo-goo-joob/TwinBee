#pragma once
#include "flyingobj.h"
#include "Game.h"

class BulletGen{
public:
    bool on, prev;
    int lastShoot;
    static const int shootTime = 5;
    static BulletGen& Instance()
    {
        static BulletGen b;
        return b;
    }
    void Gen(){
        if (on && !prev){
            Game& game = Game::Instance();
            FlyingObj* item = new FlyingObj();
            game.bulls.push_back(item);
            prev = true;
        }
    }
    void Update(const Notifer& n){
        if(n.getStage() - lastShoot >= BulletGen::shootTime){
            lastShoot = n.getStage();
            Gen();
        }
    }
private:
    BulletGen(){
        on = false;
        prev = false;
        lastShoot = -1;
    }
    ~BulletGen(){}
    BulletGen(BulletGen const&) = delete;
    BulletGen& operator= (BulletGen const&) = delete;
};
