#pragma once
#include <memory>
#include "Engine/Core.h"
#include "Engine/Modules/ModulesManager.h"
#include "Engine/Modules/Window/WindowModule.h"
#include "Engine/Modules/Input/InputModule.h"
#include "Engine/Modules/Controller/ControllerModule.h"
#include "Engine/Modules/World/WorldModule.h"
#include "Engine/Modules/Display/DisplayModule.h"

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