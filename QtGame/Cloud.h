#pragma once
#include "GameItem.h"
class Cloud :
	public GameItem
{
	int _score;
public:
	Cloud();
	~Cloud();
    //static void SetDafaultParams(const QSettings & settings);
};

