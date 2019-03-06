#pragma once
#include "Game.h"

bool GameItem::isIn(){
    Game& game = Game::Instance();
    return (0 < _x && _x < game.width() && 0 <_y && _y <game.height() );
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
    QImage img(25, 25, QImage::Format_RGB32);
    img.load("images/Bee1.png");
    QImage img2 = img.scaled(50, 50, Qt::KeepAspectRatio);
    painter.drawImage(b.X(),b.Y(),img2);
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
    QImage img(0, 0, QImage::Format_RGB32);
    img.load("images/cloud.jpg");
    QImage img2 = img.scaled(100, 50, Qt::KeepAspectRatio);
    painter.drawImage(c.X(),c.Y(),img2);

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
    QColor gray("#A52A2A");
    Qt::BrushStyle style = Qt::SolidPattern;
    QBrush brush(gray, style);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(b.X(),b.Y(), 15,15);
    painter.end();
}

void DrawGameItems::visit(RedEnemy &r){
    QPainter painter(e);
    QColor red("#ff00ff");
    Qt::BrushStyle style = Qt::SolidPattern;
    QBrush brush(red, style);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.drawRect(r.X(),r.Y(), 25,25);
    painter.end();
}

void DrawGameItems::visit(BlueEnemy &b){
    QPainter painter(e);
    QColor blue("#0000CD");
    Qt::BrushStyle style = Qt::SolidPattern;
    QBrush brush(blue, style);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.drawRect(b.X(),b.Y(), 25,25);
    painter.end();
}
