#pragma once
#include "Bee.h"
#include "Enemy.h"
#include "Cloud.h"
#include "flyingobj.h"
#include "initialization.h"


class Game
{
    Game(){
        Initialization& ini = Initialization::Instance();
        _level = ini.Sett("setgame/level", 1);
        if (_level < 0){
            _level = 1;
        }
        _play = true;
        _width = ini.Sett("setgame/width", 900);
        if (_width < 0){
            _width = 900;
        }
        _height = ini.Sett("setgame/height", 700);
        if (_width < 0){
            _width = 700;
        }
        _score = ini.Sett("setgame/score");
        if (_score < 0){
            _score = 0;
        }
        setLevel1();
    }
    ~Game(){
        delete bee;
        delete factory;
        for(auto c: items){
            delete c;
        }
    }
	Game(Game const&) = delete;
    Game& operator= (Game const&) = delete;
    EnemyFactory *factory;
    int _width, _height;
    int _score;
    bool _play;
    int _level;
public:
    Bee *bee;
    QVector<GameItem*> items;
    QVector<Client*> enemes;
    void setLevel1(){
        bee = new Bee();
        factory = new RedEnemyFactory;
        for (int i = 0; i < 3; i++) {
            Client* enemy = static_cast<Client*>(new Client(factory));
            enemes.push_back(enemy);
        }
        for (int i = 0; i < 3; i++) {
            GameItem* item = static_cast<GameItem*>(new Cloud);
            items.push_back(item);
        }
        GameItem* item = static_cast<GameItem*>(new FlyingObj(bee->x(), bee->y() - 50));
        items.push_back(item);
    }
	static Game& Instance()
    {
		static Game g;
		return g;
    }
    void Draw(QMainWindow *e)
    {
        DrawGameItems visitor(e);
        for(auto c: enemes){
            c->access(visitor);
        }
        for(auto c: items){
            c->access(visitor);
        }
        bee->access(visitor); // i've changed the place of draw function
        //bee->Draw(e);
    }
    void Move(){}
	int width() const { return _width; }
    int height() const { return _height; }
    int score() const { return _score; }
	bool play() const { return _play; }
    int level() const { return _level; }
    void height(int height) { _height = height; }
    void width(int width) { _width = width; }
    void score(int score) { _score = score; }
    void play(bool play) { _play = play; }
    void level(int level) { _level = level; }
};
