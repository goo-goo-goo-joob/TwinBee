#pragma once
#include "flyingobj.h"
#include <cmath>

//class visitor
class Bell :
    public FlyingObj
{
    int _score;
    int _x0;
    int _y0;
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
        _x =  _x0 + 10.0 * (float)(n.getStage() - start) / (float)n.getPeriod();
        _y -= (0.3 - ((float)n.getStage() - (float)start) / (float)n.getPeriod()) * 3.0;
    }
    void Move1(const Notifer& n){
        _y -= (0.3 - ((float)n.getStage() - (float)start) / (float)n.getPeriod()) * 3.0;
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
