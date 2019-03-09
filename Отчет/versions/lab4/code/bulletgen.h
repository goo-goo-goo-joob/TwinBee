#pragma once
#include "flyingobj.h"
#include "Game.h"

class BulletGen{
public:
    bool on;

    static const int shootTime = 15;
    static BulletGen& Instance()
    {
        static BulletGen b;
        return b;
    }
    void Gen(){
        Game& game = Game::Instance();
        FlyingObj* item = new FlyingObj();
        game.bulls.push_back(item);
    }
    void Update(const Notifer& n){
        if((n.getStage() - lastShoot >= BulletGen::shootTime) && on && !isShooted){
            lastShoot = n.getStage();
            isShooted = true;
            Gen();
        }
        if (!on){
            isShooted = false;
        }
    }
private:
    int lastShoot;
    bool isShooted;
    BulletGen(){
        on = false;
        isShooted = false;
        lastShoot = -1;
    }
    ~BulletGen(){}
    BulletGen(BulletGen const&) = delete;
    BulletGen& operator= (BulletGen const&) = delete;
};
