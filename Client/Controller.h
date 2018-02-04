#pragma once
#include <unordered_map>
#include <array>
#include "ActionCommand.h"
#include "InputManager.h"
#include "Array.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Controller

class Controller
{
public:
	enum class Button : uint8_t
	{
		Rotate, MoveForward, MoveBackward, MoveLeft, MoveRight,
		PrimaryAttack, SecondaryAttack,
		FirstAbility, SecondAbility, ThridAbility, FourthAbility,
		Count
	};

private:
	typedef std::unordered_map<ActionCommand::ID, ActionCommand::ExecutionData> ActionsExecuting;

public:
	Controller();

	// returns ActionCommand that is assigned to given button but only if it is possible for this action to execute
	ActionCommand::ID pressButton(Controller::Button button);
	// returns ActionCommand that is assigned to given button but only if this action isn't already ending
	ActionCommand::ID releaseButton(Controller::Button button);

	void controlCharacter(class Character& executor, float_t deltaTime);

private:
	ActionsExecuting actionsExecuting;
};

// Controller
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ControllerManager

class ControllerManager
{
	typedef Array<std::pair<Controller::Button, KeyState>, RawInputPack::maxInput> ControllerButtons;
	typedef Array<std::pair<ActionCommand::ID, ActionCommand::ExecutionStage>, RawInputPack::maxInput> ActionCommands;

public:
	void startUp();
	void shoutDown();
	
	ActionCommands useController();
	
	void setCharacterToControl(Controller* mainCharacterController);

	static ActionCommand::ID getActionIDByButton(Controller::Button button);

private:
	ActionCommands		getCurrentActionsToCommand();
	ControllerButtons	getTranslatedCurrentRawInput();

private:
	Controller* mainCharacterController;

	std::unordered_map<RawKeyCode, Controller::Button> keyboardBindings;
	std::unordered_map<RawKeyCode, Controller::Button> mouseBindings;

	static Array<ActionCommand::ID, (uint8_t)Controller::Button::Count> actionIDByButton;
};

// ControllerManager
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////