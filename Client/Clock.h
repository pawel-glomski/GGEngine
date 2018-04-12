#pragma once
#include <chrono>

class Clock
{
	using TimePoint_t = std::chrono::high_resolution_clock::time_point;

	using Clock_t = std::chrono::high_resolution_clock;

	using Duration_t = std::chrono::duration<float_t>;

public:

	Clock();


	float_t getDeltaTime();

	float_t getWorldTime();

private:

	const TimePoint_t first; // assigned at Clock's constructor

	TimePoint_t last;

	float_t worldTime = 0;
};