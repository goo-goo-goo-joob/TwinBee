#pragma once
#include <iostream>
using namespace std;
class GameItem
{
	int _x, _y;
	bool _play;
public:
	GameItem();
	virtual ~GameItem();
	virtual void Draw() = 0;
	virtual void Move() = 0;
};

