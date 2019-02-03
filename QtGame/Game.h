#pragma once
#include "GameItem.h"
#include "Bee.h"
#include "Enemy.h"
enum Level { FIRST = 1, SECOND = 2 };
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
    void SetDafaultParams(const QSettings & sett){
        _level = Level(sett.value("setgame/level", 0).toInt());
        _play = true;
        _width = sett.value("setgame/wigth", 900).toInt();
        _height = sett.value("setgame/height", 700).toInt();
        _score = sett.value("setgame/score", 0).toInt();
    }
	void Draw();
	void Move();
	int width() const { return _width; }
    int height() const { return _height; }
    int score() const { return _score; }
	bool play() const { return _play; }
	Level level() const { return _level; }
    void height(int height) { _height = height; }
    void width(int width) { _width = width; }
    void score(int score) { _score = score; }
    void play(bool play) { _play = play; }
    void level(Level level) { _level = level; }
};

