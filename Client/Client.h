#pragma once
#include "Clock.h"
#include "ModulesHolder.h"
#include "WindowModule.h"
#include "InputModule.h"
#include "ControllerModule.h"
#include "ObjectModule.h"
#include "DisplayModule.h"


class Client
{
public:

	void play();

private:

	// order of adding modules determines the order of modules startup, update and shotdown!
	ModulesHolder
	<
		WindowModule, 
		InputModule, 
		ControllerModule, 
		ObjectModule,
		DisplayModule
	> modules;

	Clock clock;
};