#pragma once
#include <chrono>
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
	float calcDeltaTime(std::chrono::high_resolution_clock::time_point & now, std::chrono::high_resolution_clock::time_point& last);

private:

	ResourceManager resourceManager;
	AudioManager	audioManager;
	DisplayManager	displayManager;
	ControllerManager controllerManager;
};