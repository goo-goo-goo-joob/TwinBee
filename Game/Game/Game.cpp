#include "Game.h"






void Game::Draw()
{
	factory = new RedEnemyFactory;
	//factory = new BlueEnemyFactory;
	Client *c = new Client(factory);
	c->Draw();
}

void Game::Move()
{
}
