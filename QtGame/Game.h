#pragma once
#include "Bee.h"
#include "Enemy.h"
#include "Cloud.h"
#include "Bell.h"
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
        Initialization& ini = Initialization::Instance();
        ini.Save("setgame", "level", 1);
        ini.Save("setgame", "score", 0/*_score*/);
        ini.Save("logs", "no logs", 1);
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
        for (auto it = bulls.begin(); it != bulls.end(); it++) {
            delete *it;
            bulls.erase(it);
            it--;
        }
        for (auto it = bells.begin(); it != bells.end(); it++) {
            delete *it;
            bells.erase(it);
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
    QVector<Cloud*> items;
    QVector<Client*> enemes;
    QVector<Bell*> bells;
    void Collide(){
        for (auto b: bulls){
            for (auto i: enemes){
                if (b->X() > i->e->X() && b->X() + 10 < i->e->X() + 25 &&
                        b->Y() < i->e->Y() + 25 && b->Y() + 10 > i->e->Y()){
                    i->e->_play = false;
                    b->_play = false;
                    _score += i->e->score();
                }
            }
        }
        for (auto b: bulls){
            for (auto i: items){
                if (b->X() > i->X() && b->X() + 10 < i->X() + 50 &&
                        b->Y() < i->Y() + 30 && b->Y() + 10 > i->Y()){
                    if(i->haveBell){
                        i->haveBell = false;
                        bells.push_back(new Bell(i->X() + 15, i->Y()));
                    }
                    b->_play = false;
                }
            }
        }
        for (auto b: bulls){
            for (auto i: bells){
                if (b->X() > i->X() && b->X() + 10 < i->X() + 15 &&
                        b->Y() < i->Y() + 15 && b->Y() + 10 > i->Y()){
                    i->moveType = 1;
                    i->start = Notifer::Instance().getStage();
                    b->_play = false;
                }
            }
        }
        for (auto i: bells){
            if (i->X() > bee->X() && i->X() + 15 < bee->X() + 25 &&
                    i->Y() < bee->Y() + 25 && i->Y() + 15 > bee->Y()){
                _score += i->score();
                i->_play = false;
            }
        }
    }
    void Update(const Notifer& n) {
        Collide();
    }
    void setLevel1(){
        bee = new Bee();
        EnemyFactory *factory = new BlueEnemyFactory;
        for (int i = 0; i < 3; i++) {
            Client* enemy = static_cast<Client*>(new Client(factory));
            enemes.push_back(enemy);
        }
        for (int i = 0; i < 3; i++) {
            Cloud* item = static_cast<Cloud*>(new Cloud);
            items.push_back(item);
        }
        delete factory;
    }
    void Clear(){
        for (auto it = bulls.begin(); it != bulls.end(); it++) {
            if (!(*it)->isIn() || !(*it)->_play){
                delete *it;
                bulls.erase(it);
                it--;
            }
        }
        for (auto it = enemes.begin(); it != enemes.end(); it++) {
            if (!(*it)->e->isIn() || !(*it)->e->_play){
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
        for (auto it = bells.begin(); it != bells.end(); it++) {
            if (!(*it)->isIn() || !(*it)->_play){
                delete *it;
                bells.erase(it);
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
        for(auto c: bells){
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
