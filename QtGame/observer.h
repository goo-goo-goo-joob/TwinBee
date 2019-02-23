#pragma once
#include <iostream>
#include <vector>
#include <time.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <string.h>
#include <algorithm>
#include <QTimer>
using namespace std ;

//GameItem is class Observer
class GameItem;

//observable object
class Notifer: public QObject
{
      Q_OBJECT
public:
    static Notifer& Instance()
    {
        static Notifer n;
        return n;
    }
    void Subscribe(GameItem* item);
    void Unsubscribe(GameItem* item);

    int getStage() const
    {
        return stage;
    }
    int getPeriod() const
    {
        return period;
    }
public slots:
    void Notify();
protected:
    vector<GameItem*> _items;
private:
    Notifer();
    ~Notifer();
    Notifer(Notifer const&) = delete;
    Notifer& operator= (Notifer const&) = delete;
    QTimer *timer;
    int stage;
    int period;
};

