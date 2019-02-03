#pragma once
#include "GameItem.h"

//Abstract base product
class Enemy :
	public GameItem
{
public:
    Enemy() {}
    ~Enemy() {}
};

//Concrete product type Red
class RedEnemy :
	public Enemy
{
    static int _score;
    static int _speed;
public:    
    RedEnemy(){
        _x = 0;
        _y = 0;
    }
    static void SetDafaultParams(const QSettings & sett){
        _score = sett.value("setscore/RedEnemy", 0).toInt();
        _speed = sett.value("setspeed/RedEnemy", 0).toInt();
    }
    void Draw() { cout << "RedEnemy appeared (" <<_x<<"," <<_y<<")"<< endl; }
    void Move() {
        _x += _speed;
        _y += _speed;
    }

    ~RedEnemy(){}
};

//Concrete product type Blue
class BlueEnemy :
	public Enemy
{
    static int _score;
    static int _speed;
public:
    BlueEnemy(){
        _x = 0;
        _y = 0;
    }
    void Draw() { cout << "BlueEnemy appeared (" <<_x<<"," <<_y<<")"<< endl; }
    void Move() {
        _x -= _speed;
        _y += _speed;
    }
    static void SetDafaultParams(const QSettings & sett){
        _score = sett.value("setscore/BlueEnemy", 0).toInt();
        _speed = sett.value("setspeed/BlueEnemy", 0).toInt();
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
	void Draw()
	{
		Enemy *e = _f->CreateEnemy();
		e->Draw();
	}
};
