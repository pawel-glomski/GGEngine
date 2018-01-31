#include "ActionCommand.h"
#include "Character.h"

std::array<ActionCommand*, (uint16_t)ActionCommand::ID::Count> ActionCommand::actionByID;

ActionCommand * ActionCommand::getActionByID(ActionCommand::ID id)
{
	return actionByID[(uint8_t)id];
}

ActionCommand::ID ActionCommand::getID() const
{
	return id;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

NoActionCommand::NoActionCommand()
{
	//////////////////////////////
	// must have
	id = ID::NoActionCommand;
	actionByID[(uint8_t)id] = this;
	// must have
	//////////////////////////////
}

bool NoActionCommand::execute(Character & executor, ExecutionData & data, float_t deltaTime) const
{
	std::cout << "Do Nothing" << std::endl;
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

WalkForwardCommand::WalkForwardCommand()
{	
	//////////////////////////////
	// must have
	id = ID::WalkForwardCommand;
	actionByID[(uint8_t)id] = this;
	// must have
	//////////////////////////////
	repeatable = true;
	playerStopable = true;
}

bool WalkForwardCommand::execute(Character & executor, ExecutionData & data, float_t deltaTime) const
{
	data.actionExecutingTime += deltaTime;
	executor.moveInGlobal({ 0,-100 * deltaTime });
	if (playerStopable && data.endAction)
		return true;

	return !repeatable;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

WalkBackwardCommand::WalkBackwardCommand()
{
	//////////////////////////////
	// must have
	id = ID::WalkBackwardCommand;
	actionByID[(uint8_t)id] = this;
	// must have
	//////////////////////////////
	repeatable = true;
	playerStopable = true;
}

bool WalkBackwardCommand::execute(Character & executor, ExecutionData & data, float_t deltaTime) const
{
	data.actionExecutingTime += deltaTime;
	executor.moveInGlobal({ 0,100 * deltaTime });
	if (playerStopable && data.endAction)
		return true;

	return !repeatable;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

WalkLeftCommand::WalkLeftCommand()
{
	//////////////////////////////
	// must have
	id = ID::WalkLeftCommand;
	actionByID[(uint8_t)id] = this;
	// must have
	//////////////////////////////
	repeatable = true;
	playerStopable = true;
}

bool WalkLeftCommand::execute(Character & executor, ExecutionData & data, float_t deltaTime) const
{
	data.actionExecutingTime += deltaTime;
	executor.moveInGlobal({ -100 * deltaTime,0 });
	if (playerStopable && data.endAction)
		return true;

	return !repeatable;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

WalkRightCommand::WalkRightCommand()
{
	//////////////////////////////
	// must have
	id = ID::WalkRightCommand;
	actionByID[(uint8_t)id] = this;
	// must have
	//////////////////////////////
	repeatable = true;
	playerStopable = true;
}

bool WalkRightCommand::execute(Character & executor, ExecutionData & data, float_t deltaTime) const
{
	data.actionExecutingTime += deltaTime;
	executor.moveInGlobal({ 100 * deltaTime,0 });
	if (playerStopable && data.endAction)
		return true;

	return !repeatable;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////