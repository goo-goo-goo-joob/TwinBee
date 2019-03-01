#include "Cloud.h"
#include "observer.h"

Cloud::Cloud(){
    Initialization& ini = Initialization::Instance();
    _speed = ini.Sett("setspeed/Cloud");
    if (_speed < 0){
        _speed = 0;
    }
    int x = ini.Sett("setgame/width", 900);
    if (x < 0){
        x = 900;
    }
    x -= 50;
    int y = ini.Sett("setgame/height", 700);
    if (y < 0){
        y = 700;
    }
    y /= 2;
    _x = rand()%x;
    _y = rand()%y;
    Notifer::Instance().Subscribe(this);
}

Cloud::~Cloud() {
    Notifer::Instance().Unsubscribe(this);
}

void Cloud::access(Visitor &v) {
    v.visit(*this);
}
void Cloud::Move(){
    _y+=_speed;
}
void Cloud::Update(const Notifer& n){
    if(n.getStage() % 30 == 0){
        cout << "HERHOVOE OBLAKO!!!" << endl;

    }
    Move();
}
