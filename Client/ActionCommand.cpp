#include "ActionCommand.h"
#include "Character.h"

WalkForwardCommand::WalkForwardCommand()
{
	repeatable = true;
	playerStopable = true;
}

bool WalkForwardCommand::execute(Character & executor, ExecutionData & data, float_t deltaTime)
{
	executor.moveInGlobal({ 0,-100 * deltaTime });
	if (playerStopable && data.stopAction)
		return true;

	return !repeatable;
}


WalkBackwardCommand::WalkBackwardCommand()
{
	repeatable = true;
	playerStopable = true;
}

bool WalkBackwardCommand::execute(Character & executor, ExecutionData & data, float_t deltaTime)
{
	executor.moveInGlobal({ 0,100 * deltaTime });
	if (playerStopable && data.stopAction)
		return true;

	return !repeatable;
}


WalkLeftCommand::WalkLeftCommand()
{
	repeatable = true;
	playerStopable = true;
}

bool WalkLeftCommand::execute(Character & executor, ExecutionData & data, float_t deltaTime)
{
	executor.moveInGlobal({ -100 * deltaTime,0 });
	if (playerStopable && data.stopAction)
		return true;

	return !repeatable;
}

WalkRightCommand::WalkRightCommand()
{
	repeatable = true;
	playerStopable = true;
}
bool WalkRightCommand::execute(Character & executor, ExecutionData & data, float_t deltaTime)
{
	executor.moveInGlobal({ 100 * deltaTime,0 });
	if (playerStopable && data.stopAction)
		return true;

	return !repeatable;
}
