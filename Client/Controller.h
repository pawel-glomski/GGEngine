#pragma once
#include <unordered_map>
#include <unordered_set>
#include "InputManager.h"
#include "ActionCommand.h"

class Controller
{
	typedef std::unordered_map<ActionCommand*, ActionCommand::ExecutionData> ActionsExecuting;

public:
	Controller();

	void setControllerID(std::string ID);
	std::string getControllerID() const;

	void giveActionCommand(ActionCommand * actionCommand);
	void executeActionCommands(class Character& executor, float_t deltaTime);

private:
	std::string ID;
	ActionsExecuting actionsExecuting;
};

