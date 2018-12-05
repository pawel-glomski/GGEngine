#pragma once
#include <memory>
#include "GGEngine/Core.h"
#include "GGEngine/Modules/ModulesManager.h"
#include "GGEngine/Modules/Window/WindowModule.h"
#include "GGEngine/Modules/Input/InputModule.h"
#include "GGEngine/Modules/Controller/ControllerModule.h"
#include "GGEngine/Modules/World/WorldModule.h"
#include "GGEngine/Modules/Display/DisplayModule.h"

class Application
{
public:

	virtual void run() = 0;

	virtual ~Application() = default;

protected:

	void updateClock();

protected:

	// order of adding modules determines the order of modules startup, update and (reversed) shutdown!
	ModulesManager
		<
		WindowModule,
		InputModule,
		ControllerModule,
		WorldModule,
		DisplayModule
		> engine;
};

std::unique_ptr<Application> makeApplication();