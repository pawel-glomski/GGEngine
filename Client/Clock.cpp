#include "Clock.h"

Clock::Clock() : first(Clock_t::now()), last(Clock_t::now())
{
}

float_t Clock::getDeltaTime()
{
	TimePoint_t now = Clock_t::now();
	Duration_t dt(now-last);
	last = now;
	return dt.count();
}

float_t Clock::getWorldTime()
{
	TimePoint_t now = Clock_t::now();
	Duration_t diff(now - first);
	return diff.count();
}
