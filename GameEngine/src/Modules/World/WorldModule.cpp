#include "Engine/Modules/World/WorldModule.h"
#include "Engine/Utility/Time/Clock.h"

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
