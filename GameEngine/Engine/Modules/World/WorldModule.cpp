#include "WorldModule.h"
#include "Utilities/Time/Clock.h"

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
