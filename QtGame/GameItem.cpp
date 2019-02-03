#pragma once
#include "GameItem.h"
#include "Game.h"
#include"Enemy.h"

int RedEnemy::_speed;

GameItem::GameItem()
{
}


GameItem::~GameItem()
{
}


bool GameItem::isIn(){
    Game& game = Game::Instance();
    return (0 < _x && _x < game.width() && 0 <_y && _y <game.height() );
}
