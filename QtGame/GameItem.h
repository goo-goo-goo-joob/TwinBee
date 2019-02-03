#pragma once
#include <iostream>
#include "QSettings"

using namespace std;
class GameItem
{
protected:
	int _x, _y;
	bool _play;
public:
	GameItem();
	virtual ~GameItem();
	virtual void Draw() = 0;
	virtual void Move() = 0;
    bool isIn();
};

