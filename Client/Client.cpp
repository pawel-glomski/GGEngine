#include <chrono>
#include <SFML/Network.hpp>
#include "stdInclude.h"
#include "Client.h"

void Client::play()
{
	startUp();
	float deltaTime = 0;
	std::chrono::high_resolution_clock::time_point last = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::time_point now = last;

	while (displayManager.getWin()->isOpen())
	{
		RawInputReceiver::instance().catchInput();
		controllerManager.useController();

		deltaTime = calcDeltaTime(now, last);

		World::instance().update(deltaTime);
		displayManager.displayWorld();
	}

	shoutDown();
}

void Client::startUp()
{
	MemoryManager::instance().startUp();
	displayManager.startUp();
	RawInputReceiver::instance().startUp(displayManager.getWin());
	controllerManager.startUp();
	World::instance().startUp(controllerManager);
}

void Client::shoutDown()
{
	World::instance().shoutDown();
	controllerManager.shoutDown();
	RawInputReceiver::instance().shoutDown();
	displayManager.shoutDown();
	MemoryManager::instance().shoutDown();
}

float Client::calcDeltaTime(std::chrono::high_resolution_clock::time_point & now, std::chrono::high_resolution_clock::time_point & last)
{
	float dt = 0.f;
	now = std::chrono::high_resolution_clock::now();
	dt = (now - last).count() / 1000000000.f;
	last = now;
	return dt;
}
