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

void Controller::activateControllerButton(const InputSettings::ControllerButton & controllerButton)
{
	// check if current executing orders make it possible to execute this new order
	// if it is possible, execute this action
	actionsExecuting.insert(actionsSet[controllerButton]);

}

void Controller::executeActions(Character & executor)
{
	for (auto& action : actionsExecuting)
		action->execute(executor);

}
