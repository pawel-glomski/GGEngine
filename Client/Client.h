#pragma once
#include "ModulesHolder.h"
#include "WindowModule.h"
#include "DisplayModule.h"
#include "EntityModule.h"


class Client
{
public:

	void play();

private:

	// order of adding modules determines the order of modules startup, update and shout down!
	ModulesHolder<WindowModule, EntityModule, DisplayModule> modules;
};