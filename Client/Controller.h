#pragma once
#include <unordered_map>
#include <array>
#include "ActionCommand.h"
#include "InputManager.h"
#include "Array.h"

class Controller
{
public:
	enum class Button : uint8_t
	{
		Unknown, MoveForward, MoveBackward, MoveLeft, MoveRight,
		PrimaryAttack, SecondaryAttack,
		FirstAbility, SecondAbility, ThridAbility, FourthAbility,
		Count
	};

private:
	typedef std::unordered_map<ActionCommand::ID, ActionCommand::ExecutionData> ActionsExecuting;

public:
	Controller();

	// returns ActionCommand that is assigned to given button and tries to execute that command
	ActionCommand::ID pressButton(Controller::Button button);
	void giveActionCommand(ActionCommand::ID actionID);
	void controlCharacter(class Character& executor, float_t deltaTime);

private:
	ActionsExecuting actionsExecuting;
};

class ControllerManager
{
	typedef Array<Controller::Button, RawInputPack::maxInput> ControllerButtons;
	typedef Array<ActionCommand::ID, RawInputPack::maxInput> ActionCommands;

public:
	void startUp();
	void shoutDown();
	
	ActionCommands useController(const RawInputPack & rawInput);
	
	void setCharacterToControl(Controller* mainCharacterController);

	static ActionCommand::ID getActionIDByButton(Controller::Button button);

private:
	void fromRawInputToControllerButtons(ControllerButtons & buffer, const RawInputPack & inputToTranslate);

private:
	Controller* mainCharacterController;

	std::unordered_map<RawKeyCode, Controller::Button> keyboardBindings;
	std::unordered_map<RawKeyCode, Controller::Button> mouseBindings;

	static Array<ActionCommand::ID, (uint8_t)Controller::Button::Count> actionIDByButton;
};