#pragma once
#include "GameItem.h"
#include "initialization.h"

//class visitor
class FlyingObj :
    public GameItem
{
protected:
    int _speed;
public:
    FlyingObj();
    ~FlyingObj();
    void access(Visitor &v) override {
        v.visit(*this);
    }
    void Update(const Notifer& n) override;
    void Move(){
        _y -= _speed;
    }
};
