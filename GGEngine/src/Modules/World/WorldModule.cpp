#include "GGEngine/pch.h"
#include "GGEngine/Modules/World/WorldModule.h"
#include "GGEngine/Utility/Time/Clock.h"

void WorldModule::startUp()
{
}

void WorldModule::update()
{
	world.update(SimulationClock::getDeltaTime());
}

void WorldModule::shutdown()
{
	world.entityManager.clear();
}
