#include "Controller.h"
#include "Character.h"
#include "stdInclude.h"
#include "InputManager.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Controller

Controller::Controller()
{
	actionsExecuting.reserve(10);
}

ActionCommand::ID Controller::pressButton(Controller::Button button)
{
	ActionCommand::ID actionID = ControllerManager::getActionIDByButton(button);
	if (!actionsExecuting.count(actionID))
		actionsExecuting.emplace(std::make_pair(actionID, ActionCommand::ExecutionData()));
	else if (actionsExecuting[actionID].stage != ActionCommand::ExecutionStage::Ending)
	{
		// if button is already pressed, and stage of execution is not "ending" (as it should always be, after key release), 
		// this means, that event of button release was not catched, and if action is repeatable, it can't end
		// we must set its stage as ending and check if this action is finished (we stimulate key release) 
		// and if it is, reset its execution data (so it can start executing again)
		actionsExecuting[actionID].stage = ActionCommand::ExecutionStage::Ending;
		if (ActionCommand::getActionByID(actionID)->isFinished(actionsExecuting[actionID]))
			actionsExecuting[actionID] = ActionCommand::ExecutionData();
	}
	else 
		// return correct id only when this function acually changes something (make it return true value only once)
		return ActionCommand::ID::NoActionCommand;

	return actionID;
}

ActionCommand::ID Controller::releaseButton(Controller::Button button)
{
	ActionCommand::ID actionID = ControllerManager::getActionIDByButton(button);
	if (actionsExecuting.count(actionID) && actionsExecuting[actionID].stage != ActionCommand::ExecutionStage::Ending)
		actionsExecuting[actionID].stage = ActionCommand::ExecutionStage::Ending;
	else 
		// return correct id only when this function acually changes something (make it return true value only once)
		return ActionCommand::ID::NoActionCommand;
	return actionID;
}

void Controller::controlCharacter(Character & executor, float_t deltaTime)
{

	ASSERT((actionsExecuting.size() <= RawInputPack::maxInput), "There are to many actions executing at the same time!");

	for (auto it = actionsExecuting.begin(); it != actionsExecuting.end();)
		if (ActionCommand::getActionByID(it->first)->execute(executor, it->second, deltaTime))
			it = actionsExecuting.erase(it);	// if finished execution
		else 
			it++;
}

// Controller
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ControllerManager

Array<ActionCommand::ID, (uint8_t)Controller::Button::Count>  ControllerManager::actionIDByButton;

void ControllerManager::startUp()
{
	keyboardBindings.reserve((uint8_t)Controller::Button::Count);
	mouseBindings.reserve((uint8_t)sf::Mouse::Button::ButtonCount);

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

	// every controller button must be assigned to any action, so for safety reasons, at first, assign all buttons to no action
	for (uint8_t i = 0; i < (uint8_t)Controller::Button::Count; i++)
		actionIDByButton[i] = NoActionCommand::instance().getID();

	actionIDByButton[(uint8_t)Controller::Button::Rotate] = RotateCommand::instance().getID();
	actionIDByButton[(uint8_t)Controller::Button::MoveForward] = WalkForwardCommand::instance().getID();
	actionIDByButton[(uint8_t)Controller::Button::MoveBackward] = WalkBackwardCommand::instance().getID();
	actionIDByButton[(uint8_t)Controller::Button::MoveLeft] = WalkLeftCommand::instance().getID();
	actionIDByButton[(uint8_t)Controller::Button::MoveRight] = WalkRightCommand::instance().getID();
	actionIDByButton[(uint8_t)Controller::Button::FirstAbility] = DashCommand::instance().getID();
}

void ControllerManager::shoutDown()
{
	mainCharacterController = nullptr;
	keyboardBindings.reserve(0);
	mouseBindings.reserve(0);
}

ControllerManager::ActionCommands ControllerManager::useController()
{
	ASSERT(mainCharacterController, "There is no mainCharacterController set to use input on");
	if (!mainCharacterController)
		return ActionCommands();

	return getCurrentActionsToCommand();
}

ControllerManager::ActionCommands ControllerManager::getCurrentActionsToCommand()
{
	ActionCommands actionsToCommand;
	for (const auto & button : getTranslatedCurrentRawInput())
	{
		ActionCommand::ID actionID;
		ActionCommand::ExecutionStage stage;

		if (button.second == KeyState::Pressed)
		{
			actionID = mainCharacterController->pressButton(button.first);
			stage = ActionCommand::ExecutionStage::Beginning;
		}
		else
		{
			actionID = mainCharacterController->releaseButton(button.first);
			stage = ActionCommand::ExecutionStage::Ending;
		}
		if (actionID != ActionCommand::ID::NoActionCommand)
			actionsToCommand.push_back({ actionID, stage });
	}
	return actionsToCommand;
}

ControllerManager::ControllerButtons ControllerManager::getTranslatedCurrentRawInput()
{
	ControllerButtons buffer;
	const RawInputPack & inputToTranslate = RawInputReceiver::instance().getCurrentInput();

	for (const auto & key : inputToTranslate.rawKeys)
		if (key.divice == InputDivice::Keyboard && keyboardBindings.count(key.code))
			buffer.push_back({ keyboardBindings[key.code], key.state });
		else if (key.divice == InputDivice::Mouse && mouseBindings.count(key.code))
			buffer.push_back({ mouseBindings[key.code], key.state });
	return buffer;
}

void ControllerManager::setCharacterToControl(Controller * mainCharacterController)
{
	this->mainCharacterController = mainCharacterController;
	mainCharacterController->pressButton(Controller::Button::Rotate);	// this should always be pressed
}

// static:

ActionCommand::ID ControllerManager::getActionIDByButton(Controller::Button button)
{
	if(button < Controller::Button::Count)
		return actionIDByButton[(uint8_t)button];
	return ActionCommand::ID::NoActionCommand;
}

// ControllerManager
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
