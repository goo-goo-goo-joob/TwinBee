#pragma once
#include <iostream>

class Bee;
class Cloud;
class FlyingObj;
class RedEnemy;
class BlueEnemy;

using namespace std;

class Visitor{
public:
    virtual void visit(Bee  &b) = 0;
    virtual void visit(Cloud  &c) = 0;
    virtual void visit(FlyingObj  &f) = 0;
    virtual void visit(RedEnemy  &r) = 0;
    virtual void visit(BlueEnemy  &b) = 0;
    virtual ~Visitor() = default;
};

//element
class GameItem
{
protected:
	int _x, _y;
	bool _play;
public:
    GameItem(){
        _play = true;
    }
    virtual void access(Visitor &v) = 0;
    virtual ~GameItem() = 0;
	virtual void Draw() = 0;
	virtual void Move() = 0;
    bool isIn();
};

//concrete visitor
class DrawGameItems:
        public Visitor{
public:
    void visit(Bee &b) override{}
    void visit(Cloud &c) override{}
    void visit(FlyingObj &f) override{}
    void visit(RedEnemy &r) override{
        cout << "RedEnemy appeared " << endl;
    }
    void visit(BlueEnemy &b) override{
        cout << "BlueEnemy appeared " << endl;
    }
};
