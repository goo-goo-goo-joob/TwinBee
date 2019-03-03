#pragma once
#include <iostream>
#include <QPainter>
#include <QMainWindow>
#include "observer.h"

class Bee;
class Cloud;
class FlyingObj;
class RedEnemy;
class BlueEnemy;
class Bell;

using namespace std;

class Visitor{
public:
    virtual void visit(Bee  &b) = 0;
    virtual void visit(Cloud  &c) = 0;
    virtual void visit(FlyingObj  &f) = 0;
    virtual void visit(Bell  &b) = 0;
    virtual void visit(RedEnemy  &r) = 0;
    virtual void visit(BlueEnemy  &b) = 0;
    virtual ~Visitor() = default;
};

//element
class GameItem: public Observer
{
protected:
    int _x, _y, _speed;
public:
    bool _play;
    GameItem(){
        _play = true;
        _x = 0;
        _y = 0;
        _speed = 0;
    }
    virtual void access(Visitor &v) = 0;
    virtual ~GameItem() = 0;
    //virtual void Move() = 0;
    bool isIn();
    int X(){ return _x;}
    int Y(){ return _y;}
    int speed() {return _speed;}
    void X( int x ){ _x = x;}
    void Y( int y ){ _y = y;}
};

//concrete visitor
class DrawGameItems:
        public Visitor{
private:
    QMainWindow *e;
public:
    DrawGameItems(QMainWindow *event): e(event){}
    void visit(Bee &b)override ;
    void visit(Cloud &c) override;
    void visit(FlyingObj &f) override;
    void visit(Bell  &b) override;
    void visit(RedEnemy &r) override;
    void visit(BlueEnemy &b) override;
};

//concrete visitor
//class MoveGameItems:
//        public Visitor{
//public:
//    void visit(Bee &b)override;
//    void visit(Cloud &c) override{}
//    void visit(FlyingObj &f) override{}
//    void visit(RedEnemy &r) override{}
//    void visit(BlueEnemy &b) override{}
//};
