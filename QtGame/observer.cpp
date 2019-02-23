#include "observer.h"
#include "GameItem.h"

Notifer::Notifer() {
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(Notify()));
    stage = 0;
    period = 100;
    timer->setInterval(period);
    timer->start();
}

Notifer::~Notifer() {
    delete timer;
}

void Notifer::Subscribe(GameItem *item)
{
    _items.push_back(item);
}

void Notifer::Unsubscribe(GameItem *item)
{
    auto it = find(_items.begin(), _items.end(), item);
    if ( it != _items.end() ){
        _items.erase(it);
    }
}

void Notifer::Notify(){
    stage++;
    for(auto item: _items)
        item->Update(this);
}
