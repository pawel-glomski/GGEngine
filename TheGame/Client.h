#pragma once
#include "SettingsManager.h"
#include "World.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "DisplayManager.h"
#include "AudioManager.h"


class Client
{
private:
	Client();

public:
	static Client& instance();

	void play();

private:

	ResourceManager	resources;
	World			world;
	DisplayManager	display;
	AudioManager	audio;
	InputManager	input;
	SettingsManager	settings;
};