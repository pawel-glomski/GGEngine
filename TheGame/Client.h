#pragma once
#include "Settings.h"
#include "World.h"
#include "InputHandler.h"


class Client
{
private:
	Client();

public:
	static Client& instance();

	void play();

private:
	sf::RenderWindow window;

	World world;
	InputHandler inputHandler;
	// audio module
	// graphics module - animations, effects
	Settings settings;
};