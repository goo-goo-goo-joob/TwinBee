#pragma once
#include "Game.h"
#include "GameItem.h"

bool GameItem::isIn(){
    Game& game = Game::Instance();
    return (0 < _x && _x < game.width() && 0 <_y && _y <game.height() );
}

GameItem::~GameItem()
{
}
