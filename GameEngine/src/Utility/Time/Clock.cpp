#include "Engine/Utility/Time/Clock.h"
#include "Engine/Utility/Math/MathUtilities.h"
#include <iostream>
#include <SFML/System/Sleep.hpp>

const float_t SimulationClock::timestep = 1.f / 120.f;

SimulationClock::Clock_t clock;
SimulationClock::TimePoint_t last;

float_t deltaTime = SimulationClock::timestep;

float_t timeOffset = 0.f;

int32_t ticksToMake = 0;

void SimulationClock::update()
{
	if (last == TimePoint_t::Zero)
		last = clock.getElapsedTime();



	TimePoint_t sleepDuration = sf::seconds(timestep - (clock.getElapsedTime() - last).asSeconds() - timeOffset);
	//if(sleepDuration.asMilliseconds())
		sf::sleep(sleepDuration);




	TimePoint_t now = clock.getElapsedTime();

	deltaTime = (now - last).asSeconds();
	last = now;

	timeOffset += deltaTime - timestep;

	ticksToMake = int32_t(timeOffset / timestep);
	timeOffset -= ticksToMake * timestep;
}

int32_t SimulationClock::getTicksToMake()
{
	return ticksToMake + 1;
}

float_t SimulationClock::getWorldTime()
{
	return clock.getElapsedTime().asSeconds();
}


float_t SimulationClock::getDeltaTime()
{
	return deltaTime;
}
