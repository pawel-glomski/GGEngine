#pragma once
#include "World.h"
#include "InputManager.h"
#include "MemoryManager.h"
#include "ResourceManager.h"
#include "DisplayManager.h"
#include "AudioManager.h"


class Client
{
public:
	void play();

private:
	virtual void startUp();
	virtual void shoutDown();

private:

	ResourceManager resourceManager;
	AudioManager	audioManager;
	InputManager	inputManager;
	DisplayManager	displayManager;

	World			world;
};