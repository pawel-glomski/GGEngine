#pragma once
#include <cstdint>
#include <corecrt_math.h>
#include <vector>
#include <iostream>

class ActionCommand
{
public:
	// return true if finished executing
	virtual bool execute(class Character& executor) = 0;

private:

	float_t executionTime = 0;

	std::vector<float_t> timelineBreakPoints;
	uint8_t currentBreakPoint = 0;

};

class DoNothingCommand : public ActionCommand
{
public:
	// return true if finished executing
	virtual bool execute(class Character& executor) override
	{
		std::cout << "Do Nothing" << std::endl;
	}
};

class WalkForwardCommand : public ActionCommand
{
public:
	// return true if finished executing
	virtual bool execute(class Character& executor) override
	{
		std::cout << "Walk" << std::endl;
	}
};