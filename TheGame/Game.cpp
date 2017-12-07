#include "pch.h"
#include "Game.h"

Game & Game::instance()
{
	static Game instance;
	return instance;
}
