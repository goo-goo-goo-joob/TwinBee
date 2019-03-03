#pragma once
#include "flyingobj.h"
#include <cmath>

//class visitor
class Bell :
    public FlyingObj
{
    int _score;
public:
    int moveType;
    int start;
    Bell(int x, int y);
    ~Bell(){
        Notifer::Instance().Unsubscribe(this);
    }
    void access(Visitor &v) override {
        v.visit(*this);
    }
    void Move(const Notifer& n){
        _x += 0.05 * (n.getStage() - start) * cos(1.5);
        _y -= 0.05 * (n.getStage() - start) * sin(1.5) - 0.001 * (n.getStage() - start)*(n.getStage() - start);
    }
    void Move1(const Notifer& n){
        _y -= 0.05 * (n.getStage() - start) - 0.001 * (n.getStage() - start)*(n.getStage() - start);
    }
    void Update(const Notifer& n) override{
        if (!moveType)
            Move(n);
        else
            Move1(n);
    }
    bool isIn();
    int score() const { return _score; }
};
