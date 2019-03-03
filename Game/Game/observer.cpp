#include "observer.h"
#include "GameItem.h"
#include "initialization.h"

Notifer::Notifer() {
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(Notify()));
    stage = 0;
    Initialization& ini = Initialization::Instance();
    period = ini.Sett("timer/peroid", 30);
    timer->setInterval(period);
    timer->start();
}

Notifer::~Notifer() {
    delete timer;
}

void Notifer::Subscribe(Observer *item)
{
    _items.push_back(item);
}

void Notifer::Unsubscribe(Observer *item)
{
    auto it = find(_items.begin(), _items.end(), item);
    if ( it != _items.end() ){
        _items.erase(it);
    }
}

void Notifer::Notify(){
    stage++;
    for(auto item: _items)
        item->Update(*this);
}
