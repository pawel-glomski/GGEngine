#include "Controller.h"
#include "Character.h"
#include "stdInclude.h"

Controller::Controller()
{
	actionsExecuting.reserve(5);
}

void Controller::setControllerID(std::string ID)
{
	ASSERT(ID.size(), "Set empty ID");
	this->ID = std::move(ID);
}

std::string Controller::getControllerID() const
{
	ASSERT(ID.size(), "Returned empty ID");
	return ID;
}

void Controller::giveActionCommand(ActionCommand * actionCommand)
{
	// check if current executing orders make it possible to execute this new order
	// if it is possible, execute this action
	ASSERT(actionCommand, "Tried to give nullptr command");
	if (actionCommand)
	{
		if (actionsExecuting.count(actionCommand))
			actionsExecuting[actionCommand].stopAction = true;
		else
			actionsExecuting.emplace(std::make_pair(actionCommand, ActionCommand::ExecutionData()));
	}
}

void Controller::executeActionCommands(Character & executor, float_t deltaTime)
{
	ActionCommand* finishedActions[6];
	uint8_t finishedActionsCount = 0;

	for (auto& action : actionsExecuting)
	{
		action.second.actionExecutingTime += deltaTime;
		if (action.first->execute(executor, action.second, deltaTime))
			finishedActions[finishedActionsCount++] = action.first;	// if finished execution
	}


	for (uint8_t i = 0; i < finishedActionsCount; i++)
		actionsExecuting.erase(finishedActions[i]);
}
