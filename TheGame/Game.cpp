#include "pch.h"
#include "Game.h"

Game::Game()
{
	settings.loadSettings("data/settings.data");

	window.create({settings.graphics.resolutionX, settings.graphics.resolutionY}, "TheGame");
}

Game & Game::instance()
{
	static Game instance;
	return instance;
}

void Game::play()
{
	while (window.isOpen())
	{
		inputHandler.handleInputs(window, settings.getKeyBindings());
	}
}
