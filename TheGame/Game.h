#pragma once
#include "Settings.h"
#include "World.h"
#include "InputHandler.h"


class Game
{
private:
	Game();

public:
	static Game& instance();

	void play();

private:
	sf::RenderWindow window;

	World world;
	InputHandler inputHandler;
	// audio module
	// graphics module - animations, effects
	Settings settings;
};