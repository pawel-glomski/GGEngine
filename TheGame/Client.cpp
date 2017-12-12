#include "pch.h"
#include "Client.h"

Client::Client()
{
	settings.loadSettings("data/settings.data");

	window.create({settings.graphics.resolutionX, settings.graphics.resolutionY}, "TheGame");
}

Client & Client::instance()
{
	static Client instance;
	return instance;
}

void Client::play()
{
	while (window.isOpen())
	{
		inputHandler.handleGameplayInputs(window, settings.getKeyBindings());
	}
}
