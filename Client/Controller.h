#pragma once
#include <unordered_map>
#include <unordered_set>
#include "InputManager.h"
#include "ActionCommand.h"

class Controller
{
	typedef std::unordered_set<ActionCommand*> ActionsExecuting;

public:
	Controller();

	void setControllerID(std::string ID);
	std::string getControllerID() const;

	void activateControllerButton(const InputSettings::ControllerButton & controllerButton);
	void executeActions(class Character& executor);

private:
	std::string ID;
	ActionsExecuting actionsExecuting;
};

