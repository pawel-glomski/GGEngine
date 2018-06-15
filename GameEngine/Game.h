#pragma once
#include "Engine.h"

#include "Modules/Window/WindowModule.h"
#include "Modules/Input/InputModule.h"
#include "Modules/Controller/ControllerModule.h"
#include "Modules/World/WorldModule.h"
#include "Modules/Display/DisplayModule.h"


class Game
{
public:

	void run();

private:

	// order of adding modules determines the order of modules startup, update and (reversed) shutdown!
	Engine
	<
		WindowModule, 
		InputModule, 
		ControllerModule, 
		WorldModule,
		DisplayModule
	> engine;
};