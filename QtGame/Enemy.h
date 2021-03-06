#pragma once
#include "GameItem.h"
#include "initialization.h"

//Abstract base product
class Enemy :
	public GameItem
{
protected:
    int _score;
public:
    Enemy() {
        Initialization& ini = Initialization::Instance();
        _x = ini.Sett("setcoord/enemy_x") + rand()%70;
        if (_x < 0){
            _x = 0;
        }
        _y = ini.Sett("setcoord/enemy_y")  + rand()%70;
        if (_y < 0){
            _y = 0;
        }
        _score = 0;
        sizeX = 60;
        sizeY = 60;
    }
    void Update(const Notifer& n) override{}
    int score() const { return _score; }
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
        sizeX = 53;
        sizeY = 50;
        Notifer::Instance().Subscribe(this);
    }
    ~RedEnemy() override {
        Notifer::Instance().Unsubscribe(this);
    }
    void Update(const Notifer& n){
        Move();
    }
    void access(Visitor &v) override {
        v.visit(*this);
    }
    void Move() {
        _x += _speed;
        _y += _speed;
    }
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
        sizeX = 43;
        sizeY = 50;
        Notifer::Instance().Subscribe(this);
    }
    ~BlueEnemy() override {
        Notifer::Instance().Unsubscribe(this);
    }
    void Update(const Notifer& n){
        Move();
    }
    void access(Visitor &v) override {
        v.visit(*this);
      }
    void Move() {
        _x -= _speed;
        _y += _speed;
    }
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
    Enemy *e;
    //QVector<Enemy*> army;
    Client(EnemyFactory *f): _f(f) {
//        for(int i = 0; i < 3; i++){
//            Enemy *e = _f->CreateEnemy();
//            army.push_back(e);
//        }
       e = _f->CreateEnemy();
    }
    void access(Visitor &v)
	{
//        for(auto e: army)
//            e->access(v);
        e->access(v);
	}
};
