#pragma once
#include "Game.h"
#include "GameItem.h"


bool GameItem::isIn(){
    Game& game = Game::Instance();
    return (0 < _x && _x < game.width()
            && 0 <_y && _y <game.height() );
}

GameItem::~GameItem()
{
}

void DrawGameItems::visit(Bee &b){
    QPainter painter(e);
    QColor yellow("#f0d048");
    Qt::BrushStyle style = Qt::SolidPattern;
    QBrush brush(yellow, style);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(b.x(),b.y(), 25,25);
    cout << b.x() << endl;//but when Move from mainwindow goes it ramains constant :_(
    painter.save();
}

void MoveGameItems::visit(Bee &b) {
    b.x(b.x() + b.speed());
}

void DrawGameItems::visit(RedEnemy &r){
    QPainter painter(e);
    QColor red("#ff00ff");
    Qt::BrushStyle style = Qt::SolidPattern;
    QBrush brush(red, style);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(r.x(),r.y() + rand()%20, 25,25);
    painter.save();
}

void DrawGameItems::visit(BlueEnemy &b){
    QPainter painter(e);
    QColor blue("#0000CD");
    Qt::BrushStyle style = Qt::SolidPattern;
    QBrush brush(blue, style);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(b.x(),b.y() + rand()%20, 50,25);
    painter.save();
}
