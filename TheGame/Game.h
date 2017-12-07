#pragma once
#include "Settings.h"
#include "World.h"
#include "InputHandler.h"


class Game
{
private:
	Game() {};

public:
	static Game& instance();

private:

	World world;
	InputHandler inputHandler;
	// audio module
	// graphics module - animations, effects
	Settings settings;
};