#pragma once
#include "GameItem.h"

//Abstract base product
class Enemy :
	public GameItem
{
    int _score;
public:
	Enemy();
    void Move() {}
	~Enemy();
};

//Concrete product type Red
class RedEnemy :
	public Enemy
{
public:
	void Draw() { cout << "RedEnemy appeared" << endl; }
};

//Concrete product type Blue
class BlueEnemy :
	public Enemy
{
public:
	void Draw() { cout << "BlueEnemy appeared" << endl; }
};

//Abstract factory
class EnemyFactory {
public:
    virtual Enemy* CreateEnemy() = 0;
};

//Conctete factory type Red
class RedEnemyFactory :
	public EnemyFactory {
public:
    Enemy* CreateEnemy() {
        return new RedEnemy;
	}
};

//Conctete factory type Blue
class BlueEnemyFactory :
	public EnemyFactory {
public:
    Enemy* CreateEnemy() {
		return new BlueEnemy;
	}
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
