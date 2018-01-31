#include "Controller.h"
#include "Character.h"
#include "stdInclude.h"
#include "InputManager.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Controller

Controller::Controller()
{
	actionsExecuting.reserve(5);
}

ActionCommand::ID Controller::pressButton(Controller::Button button)
{
	// if action is already being executed - endAction will notify action, that controller button was released
	ActionCommand::ID actionID = ActionCommand::ID::NoActionCommand;
	actionID = ControllerManager::getActionIDByButton(button);

	giveActionCommand(actionID);

	return actionID;
}

void Controller::giveActionCommand(ActionCommand::ID actionID)
{
	if (actionsExecuting.count(actionID))
		actionsExecuting[actionID].endAction = true;
	else
		actionsExecuting.emplace(std::make_pair(actionID, ActionCommand::ExecutionData()));
}

void Controller::controlCharacter(Character & executor, float_t deltaTime)
{
	ActionCommand::ID finishedActions[6];
	uint8_t finishedActionsCount = 0;

	for (auto& action : actionsExecuting)
		if (ActionCommand::getActionByID(action.first)->execute(executor, action.second, deltaTime))
			finishedActions[finishedActionsCount++] = action.first;	// if finished execution

	for (uint8_t i = 0; i < finishedActionsCount; i++)
		actionsExecuting.erase(finishedActions[i]);
}

// Controller
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ControllerManager

Array<ActionCommand::ID, (uint8_t)Controller::Button::Count>  ControllerManager::actionIDByButton;

void ControllerManager::startUp()
{
	keyboardBindings.reserve((uint8_t)Controller::Button::Count);
	mouseBindings.reserve(sf::Mouse::Button::ButtonCount);

	// order here is important!
	actionIDByButton[(uint8_t)Controller::Button::Unknown] = NoActionCommand::instance().getID();
	actionIDByButton[(uint8_t)Controller::Button::MoveForward] = WalkForwardCommand::instance().getID();
	actionIDByButton[(uint8_t)Controller::Button::MoveBackward] = WalkBackwardCommand::instance().getID();
	actionIDByButton[(uint8_t)Controller::Button::MoveLeft] = WalkLeftCommand::instance().getID();
	actionIDByButton[(uint8_t)Controller::Button::MoveRight] = WalkRightCommand::instance().getID();

	actionIDByButton[(uint8_t)Controller::Button::FirstAbility] = NoActionCommand::instance().getID();
	actionIDByButton[(uint8_t)Controller::Button::SecondAbility] = NoActionCommand::instance().getID();
	actionIDByButton[(uint8_t)Controller::Button::ThridAbility] = NoActionCommand::instance().getID();
	actionIDByButton[(uint8_t)Controller::Button::FourthAbility] = NoActionCommand::instance().getID();
	actionIDByButton[(uint8_t)Controller::Button::PrimaryAttack] = NoActionCommand::instance().getID();
	actionIDByButton[(uint8_t)Controller::Button::SecondaryAttack] = NoActionCommand::instance().getID();

	ASSERT((actionIDByButton.currentSize() == (uint8_t)Controller::Button::Count), "There is controller button, that is not assigned to any action");

	keyboardBindings[sf::Keyboard::Key::W] = Controller::Button::MoveForward;
	keyboardBindings[sf::Keyboard::Key::S] = Controller::Button::MoveBackward;
	keyboardBindings[sf::Keyboard::Key::A] = Controller::Button::MoveLeft;
	keyboardBindings[sf::Keyboard::Key::D] = Controller::Button::MoveRight;
	keyboardBindings[sf::Keyboard::Key::Q] = Controller::Button::FirstAbility;
	keyboardBindings[sf::Keyboard::Key::E] = Controller::Button::SecondAbility;
	keyboardBindings[sf::Keyboard::Key::LControl] = Controller::Button::ThridAbility;
	keyboardBindings[sf::Keyboard::Key::Space] = Controller::Button::FourthAbility;

	mouseBindings[sf::Mouse::Button::Left] = Controller::Button::PrimaryAttack;
	mouseBindings[sf::Mouse::Button::Right] = Controller::Button::SecondaryAttack;
}

void ControllerManager::shoutDown()
{
	// this class will be usefull also in launcher, so deallocation is not needed
}

ControllerManager::ActionCommands ControllerManager::useController(const RawInputPack & rawInput)
{
	ControllerButtons buttonPressed;
	ActionCommands actionsToCommand;
	fromRawInputToControllerButtons(buttonPressed, rawInput);
	for (const auto & button : buttonPressed)
		actionsToCommand.push_back(actionIDByButton[(uint8_t)button]);

	for (const auto & action : actionsToCommand)
		mainCharacterController->giveActionCommand(action);

	return actionsToCommand;
}

void ControllerManager::fromRawInputToControllerButtons(ControllerButtons & buffer, const RawInputPack & inputToTranslate)
{
	for (const auto & key : inputToTranslate.rawKeys)
		if (key.inputDivice == InputDivice::Keyboard && keyboardBindings.count(key.code))
			buffer.push_back(keyboardBindings[key.code]);
		else if (key.inputDivice == InputDivice::Mouse && mouseBindings.count(key.code))
			buffer.push_back(mouseBindings[key.code]);
}

void ControllerManager::setCharacterToControl(Controller * mainCharacterController)
{
	this->mainCharacterController = mainCharacterController;
}

// static:

ActionCommand::ID ControllerManager::getActionIDByButton(Controller::Button button)
{
	return actionIDByButton[(uint8_t)button];
}


// ControllerManager
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
