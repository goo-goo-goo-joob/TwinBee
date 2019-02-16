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
