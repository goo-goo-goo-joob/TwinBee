#pragma once
#include "Bee.h"
#include "Enemy.h"
#include "Cloud.h"
#include "Bell.h"
#include "flyingobj.h"
#include "initialization.h"
#include <QThread>
#include <QMetaType>
#include <QQueue>
class Game;
class Worker : public QObject
{
    Q_OBJECT
    QThread workerThread;

public slots:
    void doWork();

signals:
    void resultReady();
};

class Game : public QObject, public Observer
{
    Q_OBJECT
    QThread workerThread;
    int lastUpd;
    int updTime;
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
        lastUpd = -1;
        updTime = 80;
        bee = new Bee();
        if (_level == 2)
            setLevel2();
        else
            setLevel1();
        Notifer::Instance().Subscribe(this);


        Worker *worker = new Worker;
        worker->moveToThread(&workerThread);
        connect(&workerThread, SIGNAL(finished()), worker, SLOT(deleteLater()));
        connect(this, SIGNAL(operate()), worker, SLOT(doWork()));
        connect(worker, SIGNAL(resultReady()), this, SLOT(handleResults()));
        workerThread.start();
    }
    ~Game(){
//        Initialization& ini = Initialization::Instance();
//        ini.Save("setgame", "level", 1);
//        ini.Save("setgame", "score", 0);
//        ini.Save("setgame", "lifes", 3);
//        ini.Save("logs", "no logs", 1);
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
        workerThread.quit();
        workerThread.wait();
    }
    Game(Game const&) = delete;
    Game& operator= (Game const&) = delete;
    int _width, _height;
    int _score;
    bool _play;
    int _level;

public slots:
    void handleResults() {}
signals:
    void operate();

public:
    Bee *bee;
    QVector<FlyingObj*> bulls;
    QVector<Cloud*> items;
    QVector<Client*> enemes;
    QVector<Bell*> bells;
    QQueue<QVector<int>> box;
    void Collide(const Notifer& n){
        operate();
    }
    void fromTheBox(){
        Notifer &n = Notifer::Instance();
        if(n.getStage() - lastUpd >= updTime){
            lastUpd = n.getStage();
            if(!box.isEmpty()){
                QVector<int> tmp;
                tmp = box.takeFirst();
                switch (tmp[0]){
                case 0:
                {
                    EnemyFactory *factory = new RedEnemyFactory;
                    for (int i = 0; i < tmp[1]; i++) {
                        Client* enemy = static_cast<Client*>(new Client(factory));
                        enemes.push_back(enemy);
                    }
                    break;
                }
                case 1:
                {
                    EnemyFactory *factory = new BlueEnemyFactory;
                    for (int i = 0; i < tmp[1]; i++) {
                        Client* enemy = static_cast<Client*>(new Client(factory));
                        enemes.push_back(enemy);
                    }
                    break;
                }
                }
            }
            else {
                setLevel2();
            }
        }
    }
    void Update(const Notifer& n) {
        Collide(n);
        if (n.getStage() % (7 * n.getPeriod()) == 0){
            items.push_back(static_cast<Cloud*>(new Cloud));
        }
        fromTheBox();
    }
    void setLevel1(){
        _level = 1;

        EnemyFactory *factory = new RedEnemyFactory;
        for (int i = 0; i < 3; i++) {
            Client* enemy = static_cast<Client*>(new Client(factory));
            enemes.push_back(enemy);
        }
        for (int i = 0; i < 3; i++) {
            Cloud* item = static_cast<Cloud*>(new Cloud);
            items.push_back(item);
        }
        delete factory;

        QFile file("level1.txt");
        if ((file.open(QIODevice::ReadOnly)))
        {
            while(!file.atEnd())
            {
                QVector<int> tmp;
                QString s = file.readLine();
                tmp.push_back(s.split(" ")[0].toInt());//type of enemy
                tmp.push_back(s.split(" ")[1].toInt());//number of enemies
                box.append(tmp);
            }
            file.close();
        }
    }
    void setLevel2(){
        _level = 2;

        QFile file("level2.txt");
        if ((file.open(QIODevice::ReadOnly)))
        {
            while(!file.atEnd())
            {
                QVector<int> tmp;
                QString s = file.readLine();
                tmp.push_back(s.split(" ")[0].toInt());//type of enemy
                tmp.push_back(s.split(" ")[1].toInt());//number of enemies
                box.append(tmp);
            }
            file.close();
        }
    }
    void Save(){
        Initialization& ini = Initialization::Instance();
        ini.Save("setgame", "level", _level);
        ini.Save("setgame", "score", _score);
        ini.Save("setgame", "lifes", bee->Lifes());
        ini.Save("logs", "no logs", 1);
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
