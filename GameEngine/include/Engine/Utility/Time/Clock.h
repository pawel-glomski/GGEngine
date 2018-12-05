#pragma once
#include <corecrt_math.h>
#include <stdint.h>
#include <SFML\System\Clock.hpp>

struct SimulationClock
{

	using Clock_t = sf::Clock;

	using TimePoint_t = sf::Time;


	static int32_t getTicksToMake();

	static float_t getDeltaTime();

	static float_t getWorldTime();

private:

	static void update();

public:

	static const float_t timestep;


	friend class Application;
};