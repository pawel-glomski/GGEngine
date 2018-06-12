#pragma once

#include "Engine.h"

#include "WindowModule.h"
#include "InputModule.h"
#include "ControllerModule.h"
#include "WorldModule.h"
#include "DisplayModule.h"


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