#pragma once
#include "GameItem.h"
#include "initialization.h"

//Abstract base product
class Enemy :
	public GameItem
{
protected:
    int _score;
    int _speed;
public:
    Enemy() {
        Initialization& ini = Initialization::Instance();
        _x = ini.Sett("setcoord/enemy_x");
        if (_x < 0){
            _x = 0;
        }
        _y = ini.Sett("setcoord/enemy_y");
        if (_y < 0){
            _y = 0;
        }
    }
    void Draw(QMainWindow *e) override{

    }
};
//Concrete product type Red
class RedEnemy :
	public Enemy
{
public:    
    RedEnemy(){
        Initialization& ini = Initialization::Instance();
        _score = ini.Sett("setscore/RedEnemy");
        if (_score < 0){
            _score = 0;
        }
        _speed = ini.Sett("setspeed/RedEnemy");
        if (_speed < 0){
            _speed = 0;
        }
    }
    void access(Visitor &v) override {
        v.visit(*this);
      }
    void Draw() { cout << "RedEnemy appeared "
                          "(" <<_x<<"," <<_y<<")"<< endl; }
    void Move() {
        _x += _speed;
        _y += _speed;
    }

    ~RedEnemy() {}
};
//Concrete product type Blue
class BlueEnemy :
	public Enemy
{
public:
    BlueEnemy(){
        Initialization& ini = Initialization::Instance();
        _score = ini.Sett("setscore/BlueEnemy");
        if (_score < 0){
            _score = 0;
        }
        _speed = ini.Sett("setspeed/BlueEnemy");
        if (_speed < 0){
            _speed = 0;
        }
    }
    void access(Visitor &v) override {
        v.visit(*this);
      }
    void Draw() { cout << "BlueEnemy appeared "
                          "(" <<_x<<"," <<_y<<")"<< endl; }
    void Move() {
        _x -= _speed;
        _y += _speed;
    }
    ~BlueEnemy(){}
};
//Abstract factory
class EnemyFactory {
public:
    EnemyFactory(){}
    virtual Enemy* CreateEnemy() = 0;
    //virtual ~EnemyFactory() = 0;
};
//Conctete factory type Red
class RedEnemyFactory :
	public EnemyFactory {
public:
    RedEnemyFactory() {}
    Enemy* CreateEnemy() override{
        return new RedEnemy;
    }
    ~RedEnemyFactory() {}
};
//Conctete factory type Blue
class BlueEnemyFactory :
	public EnemyFactory {
public:
    BlueEnemyFactory() {}
    Enemy* CreateEnemy() override {
		return new BlueEnemy;
	}
    ~BlueEnemyFactory() {}
};
//Working through abstract interface
class Client {
	EnemyFactory *_f;
public:
	Client(EnemyFactory *f): _f(f) {}
    void access(Visitor &v)
	{
		Enemy *e = _f->CreateEnemy();
        e->access(v);
	}
};
