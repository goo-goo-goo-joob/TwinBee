#pragma once
#include "GameItem.h"
#include "Bee.h"
#include "Enemy.h"
enum Level { FIRST, SECOND };
class Game
{
	Game();
	~Game();
	// необходимо запретить копирование
	Game(Game const&) = delete;
	Game& operator= (Game const&) = delete;
	//Bee bee;
	EnemyFactory *factory;
	int _width, _height;
	int _score;
	bool _play;
	Level _level;
public:
	static Game& Instance()
	{
		//безопасно, согласно стандарту —++11
		static Game g;
		return g;
	}
	void Draw();
	void Move();
	int width() const { return _width; }
	int heidht() const { return _height; }
	bool play() const { return _play; }
	Level level() const { return _level; }
};

