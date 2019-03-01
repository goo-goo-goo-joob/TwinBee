#pragma once
#include "Bee.h"
#include "Enemy.h"
#include "Cloud.h"
#include "flyingobj.h"
#include "initialization.h"


class Game : public Observer
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
        Notifer::Instance().Subscribe(this);
    }
    ~Game(){
        delete bee;
        for (auto it = items.begin(); it != items.end(); it++) {
            delete *it;
            items.erase(it);
            it--;
        }
        for (auto it = enemes.begin(); it != enemes.end(); it++) {
            delete *it;
            enemes.erase(it);
            it--;
        }
    }
	Game(Game const&) = delete;
    Game& operator= (Game const&) = delete;
    int _width, _height;
    int _score;
    bool _play;
    int _level;
public:
    Bee *bee;
    QVector<FlyingObj*> bulls;
    QVector<GameItem*> items;
    QVector<Client*> enemes;
    void Collide(){
        for (auto b: bulls){
            for (auto i: enemes){
                if (b->X() < i->e->X() + 20 && b->X() > i->e->X() - 20 && b->Y() > i->e->Y() - 20 && b->Y() < i->e->Y() + 20){
//                    delete i;
//                    enemes.erase(&i);
                    i->e->_play = false;
                }
            }
        }
    }
    void Update(const Notifer& n) {
        Collide();
        //cout<<")))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))0)";
    }
    void setLevel1(){
        bee = new Bee();
        EnemyFactory *factory = new BlueEnemyFactory;
        for (int i = 0; i < 1; i++) {
            Client* enemy = static_cast<Client*>(new Client(factory));
            enemes.push_back(enemy);
        }
        for (int i = 0; i < 3; i++) {
            GameItem* item = static_cast<GameItem*>(new Cloud);
            items.push_back(item);
        }
        delete factory;
    }
    void Clear(){
        //add for bulls
        for (auto it = enemes.begin(); it != enemes.end(); it++) {
            if (!(*it)->e->isIn() || !(*it)->e->_play){//((*it)->army)->isIn())
                delete *it;
                enemes.erase(it);
                it--;
            }
        }
        for (auto it = items.begin(); it != items.end(); it++) {
            if (!(*it)->isIn()){
                delete *it;
                items.erase(it);
                it--;
            }
        }
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
        for(auto c: bulls){
            c->access(visitor);
        }
        bee->access(visitor);
        Clear();
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
