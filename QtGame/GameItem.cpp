#pragma once
#include "Game.h"

bool GameItem::isIn(){
    Game& game = Game::Instance();
    return (0 < _x || _x - sizeX < game.width() || 0 <_y || _y - sizeY < game.height() );
}

GameItem::~GameItem(){}

void DrawGameItems::visit(Bee &b){
    QPainter painter(e);
//    QColor yellow("#f0d048");
//    Qt::BrushStyle style = Qt::SolidPattern;
//    QBrush brush(yellow, style);
//    painter.setBrush(brush);
//    painter.setPen(Qt::NoPen);
//    painter.drawEllipse(b.X(),b.Y(), b.SizeX(),b.SizeY());
    QImage img;
    img.load("images/Bee.png");
    img = img.scaled(b.SizeX(), b.SizeY(), Qt::KeepAspectRatio);
    painter.drawImage(b.X(),b.Y(),img);
    painter.end();
}

void DrawGameItems::visit(Cloud &c){
    QPainter painter(e);
//    QColor gray("#87CEFA");
//    Qt::BrushStyle style = Qt::SolidPattern;
//    QBrush brush(gray, style);
//    painter.setBrush(brush);
//    painter.setPen(Qt::NoPen);
//    painter.drawEllipse(c.X(),c.Y(), 50,30);
    QImage img;
    img.load("images/cloud.png");
    img = img.scaled(c.SizeX(), c.SizeY(), Qt::KeepAspectRatio);
    painter.drawImage(c.X(),c.Y(),img);

    painter.end();
}

void DrawGameItems::visit(FlyingObj &f){
    QPainter painter(e);
    QColor gray("#A52A2A");
    Qt::BrushStyle style = Qt::SolidPattern;
    QBrush brush(gray, style);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(f.X(),f.Y(), 10,10);
    painter.end();
}

void DrawGameItems::visit(Bell &b){
    QPainter painter(e);
//    QColor gray("#A52A2A");
//    Qt::BrushStyle style = Qt::SolidPattern;
//    QBrush brush(gray, style);
//    painter.setBrush(brush);
//    painter.setPen(Qt::NoPen);
//    painter.drawEllipse(b.X(),b.Y(), 15,15);
    QImage img;
    img.load("images/bell.png");
    img = img.scaled(b.SizeX(), b.SizeY(), Qt::KeepAspectRatio);
    painter.drawImage(b.X(),b.Y(),img);

    painter.end();
}

void DrawGameItems::visit(RedEnemy &r){
    QPainter painter(e);
//    QColor red("#ff00ff");
//    Qt::BrushStyle style = Qt::SolidPattern;
//    QBrush brush(red, style);
//    painter.setBrush(brush);
//    painter.setPen(Qt::NoPen);
//    painter.drawRect(r.X(),r.Y(), 25,25);
    QImage img;
    img.load("images/Putan.png");
    img = img.scaled(r.SizeX(), r.SizeY(), Qt::KeepAspectRatio);
    painter.drawImage(r.X(),r.Y(),img);
    painter.end();
}

void DrawGameItems::visit(BlueEnemy &b){
    QPainter painter(e);
//    QColor blue("#0000CD");
//    Qt::BrushStyle style = Qt::SolidPattern;
//    QBrush brush(blue, style);
//    painter.setBrush(brush);
//    painter.setPen(Qt::NoPen);
//    painter.drawRect(b.X(),b.Y(), 25,25);
    QImage img;
    img.load("images/Tobikame.png");
    img = img.scaled(b.SizeX(), b.SizeY(), Qt::KeepAspectRatio);
    painter.drawImage(b.X(),b.Y(),img);

    painter.end();
}
