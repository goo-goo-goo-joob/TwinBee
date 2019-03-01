#pragma once
#include "flyingobj.h"
#include "Game.h"

class BulletGen{
public:
    bool on, prev;
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
private:
    BulletGen(){
        on = false;
        prev = false;
    }
    ~BulletGen(){}
    BulletGen(BulletGen const&) = delete;
    BulletGen& operator= (BulletGen const&) = delete;
};
