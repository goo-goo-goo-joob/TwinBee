#include "Game.h"

void Worker::doWork(){
    Game &g = Game::Instance();
    Notifer &n = Notifer::Instance();
    for (auto b: g.bulls){
        for (auto i: g.enemes){
            if (b->X() > i->e->X() && b->X() + b->SizeX() < i->e->X() + i->e->SizeX() &&
                    b->Y() < i->e->Y() + i->e->SizeY() && b->Y() + b->SizeY() > i->e->Y()){
                i->e->_play = false;
                b->_play = false;
                g.score(g.score() + i->e->score());
            }
        }
    }
    for (auto b: g.bulls){
        for (auto i: g.items){
            if (b->X() > i->X() && b->X() + b->SizeX() < i->X() + i->SizeX() &&
                    b->Y() < i->Y() + i->SizeY() && b->Y() + b->SizeY() > i->Y()){
                if(i->haveBell){
                    i->haveBell = false;
                    g.bells.push_back(new Bell(b->X() + b->SizeX()/2, i->Y()));
                }
                b->_play = false;
            }
        }
    }
    for (auto b: g.bulls){
        for (auto i: g.bells){
            if (b->X() > i->X() && b->X() + b->SizeX() < i->X() + i->SizeY() &&
                    b->Y() < i->Y() + i->SizeY() && b->Y() + b->SizeY() > i->Y()){
                i->moveType = 1;
                i->start = Notifer::Instance().getStage();
                b->_play = false;
            }
        }
    }
    for (auto i: g.bells){
        if (i->X() + i->SizeX()/2 > g.bee->X() && i->X() + i->SizeX()/2 < g.bee->X() + g.bee->SizeX() &&
                i->Y() + i->SizeY()/2 > g.bee->Y() && i->Y() + i->SizeY()/2 < g.bee->Y() + g.bee->SizeY()){
            g.score(g.score() + i->score());
            i->_play = false;
        }
    }
    for (auto i: g.enemes){
        if (i->e->X() + i->e->SizeX()/2 > g.bee->X() && i->e->X() + i->e->SizeX()/2 < g.bee->X() + g.bee->SizeX() &&
                i->e->Y() + i->e->SizeY()/2 > g.bee->Y() && i->e->Y() + i->e->SizeY()/2 < g.bee->Y() + g.bee->SizeY()){
            g.bee->Update(n);
        }
    }
    emit resultReady();
}
