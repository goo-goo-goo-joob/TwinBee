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
        GameItem* item = static_cast<GameItem*>(new FlyingObj());
        game.items.push_back(item);
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
