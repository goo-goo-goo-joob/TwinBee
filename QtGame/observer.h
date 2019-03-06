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

class Notifer;

//GameItem is class Observer
class Observer
{
public:
    virtual void Update(const Notifer&) = 0;
};

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
    void Subscribe(Observer* item);
    void Unsubscribe(Observer* item);

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
    vector<Observer*> _items;
private:
    Notifer();
    ~Notifer();
    Notifer(Notifer const&) = delete;
    Notifer& operator= (Notifer const&) = delete;
    QTimer *timer;
    int stage;
    int period;
};

