#pragma once
#include <iostream>

using namespace std;
class GameItem
{
protected:
	int _x, _y;
	bool _play;
public:
    GameItem(){
        _play = true;
    }
    virtual ~GameItem() = 0;
	virtual void Draw() = 0;
	virtual void Move() = 0;
    bool isIn();
};

