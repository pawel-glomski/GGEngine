#pragma once
#include <cstdint>
#include <corecrt_math.h>
#include <vector>
#include <iostream>
#include "Singleton.h"

class ActionCommand
{
public:
	struct ExecutionData
	{
		float_t actionExecutingTime = 0.f;	// action progress
		uint8_t timelineBreakPoint = 0;		// current BreakPoint
		float_t chargingTime = 0;			// for charging actions
		float_t chargedValue = 0;
		bool stopAction = false;			// stopping action (or only part "charging" part of it)
	};

public:
	// return true if finished executing (false if it is repeatable action), may modify "ExecutionData" if it is repeatable action
	virtual bool execute(class Character& executor, ExecutionData & data, float_t deltaTime) = 0;

protected:

	bool repeatable = false;					// after finishing execution, restart whole process and keep executing (modify ExecutionData passed to "execute" member function)
	bool chargeable = false;					// if it has charging part in its timeline
	bool playerStopable = false;				// if player can stop this action (or only in some part of it (stop charging, etc.))
	float_t executionTime = 0;					// time needed to execute whole action
	std::vector<float_t> timelineBreakPoints;	// points in time, that behaviour of action changes
};

class NoActionCommand : public ActionCommand, public Singleton<NoActionCommand>
{
public:
	// return true if finished executing
	virtual bool execute(class Character& executor, ExecutionData & data, float_t deltaTime) override
	{
		std::cout << "Do Nothing" << std::endl;
		return true;
	}
};

class WalkForwardCommand : public ActionCommand, public Singleton<WalkForwardCommand>
{
public:
	WalkForwardCommand();
	virtual bool execute(class Character& executor, ExecutionData & data, float_t deltaTime) override;
};

class WalkBackwardCommand : public ActionCommand, public Singleton<WalkForwardCommand>
{
public:
	WalkBackwardCommand();
	virtual bool execute(class Character& executor, ExecutionData & data, float_t deltaTime) override;
};

class WalkLeftCommand : public ActionCommand, public Singleton<WalkForwardCommand>
{
public:
	WalkLeftCommand();
	virtual bool execute(class Character& executor, ExecutionData & data, float_t deltaTime) override;
};

class WalkRightCommand : public ActionCommand, public Singleton<WalkForwardCommand>
{
public:
	WalkRightCommand();
	virtual bool execute(class Character& executor, ExecutionData & data, float_t deltaTime) override;
};
