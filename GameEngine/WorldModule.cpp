#include "WorldModule.h"
#include "Clock.h"

void WorldModule::startUp()
{
}

void WorldModule::update()
{
	world.update(SimulationClock::getDeltaTime());
}

void WorldModule::shutdown()
{
}
