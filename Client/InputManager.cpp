#include "stdInclude.h"
#include "InputManager.h"
#include "DisplayManager.h"
#include "Controller.h"

void InputSettings::startUp()
{
	actionsSet[ControllerButton::MoveForward] = new WalkForwardCommand;
	actionsSet[ControllerButton::MoveBackward] = new WalkBackwardCommand;
	actionsSet[ControllerButton::MoveLeft] = new WalkLeftCommand;
	actionsSet[ControllerButton::MoveRight] = new WalkRightCommand;
	actionsSet[ControllerButton::FirstAbility] = new NoActionCommand;
	actionsSet[ControllerButton::SecondAbility] = new NoActionCommand;
	actionsSet[ControllerButton::ThridAbility] = new NoActionCommand;
	actionsSet[ControllerButton::FourthAbility] = new NoActionCommand;
	actionsSet[ControllerButton::PrimaryAttack] = new NoActionCommand;
	actionsSet[ControllerButton::SecondaryAttack] = new NoActionCommand;
}

void InputSettings::shoutDown()
{
	for (auto & action : actionsSet)
		delete action.second;
}


InputSettings::KeyBindings::KeyBindings()
{
	keyboardBindings.reserve((uint8_t)ControllerButton::Count);
	keyboardBindings.reserve(sf::Mouse::Button::ButtonCount);
	//...

	// if settings path was not found
	keyboardBindings[sf::Keyboard::Key::W] = ControllerButton::MoveForward;
	keyboardBindings[sf::Keyboard::Key::S] = ControllerButton::MoveBackward;
	keyboardBindings[sf::Keyboard::Key::A] = ControllerButton::MoveLeft;
	keyboardBindings[sf::Keyboard::Key::D] = ControllerButton::MoveRight;
	keyboardBindings[sf::Keyboard::Key::Q] = ControllerButton::FirstAbility;
	keyboardBindings[sf::Keyboard::Key::E] = ControllerButton::SecondAbility;
	keyboardBindings[sf::Keyboard::Key::LControl] = ControllerButton::ThridAbility;
	keyboardBindings[sf::Keyboard::Key::Space] = ControllerButton::FourthAbility;

	mouseBindings[sf::Mouse::Button::Left] = ControllerButton::PrimaryAttack;
	mouseBindings[sf::Mouse::Button::Right] = ControllerButton::SecondaryAttack;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void InputManager::startUp(const std::shared_ptr<sf::RenderWindow> & windowPtr)
{
	settings.startUp();
	windowToManage = windowPtr;
}

void InputManager::shoutDown()
{
	settings.shoutDown();
	windowToManage.reset();
}

void InputManager::setInputTargetController(Controller * controller)
{
	ASSERT(controller, "Tried to set nullptr controller");
	if(controller)
		inputTargetController = controller;
}

void InputManager::bindKeyToControllerButton(const InputSettings::ControllerButton & action, RawKeyCode keyCode, InputDivice inputDivice)
{
	if (inputDivice == InputDivice::Keyboard)
		settings.keyBindings.keyboardBindings[keyCode] = action;
	else if (inputDivice == InputDivice::Mouse)
		settings.keyBindings.mouseBindings[keyCode] = action;
}

InputManager::ActionCommands InputManager::handleGameplayInput()
{
	RawInputPack		inputToTranslate = std::move(catchInputEvents());
	ControllerButtons	controllerButtonsInput = rawInputToControllerButtonsInput(inputToTranslate);
	ActionCommands		actionCommands;
	for (const auto & button : controllerButtonsInput)
		if(settings.actionsSet.count(button))
			actionCommands.push_back(settings.actionsSet[button]);

	for (const auto & action : actionCommands)
		inputTargetController->giveActionCommand(action);

	return std::move(actionCommands);
}

InputManager::RawInputPack InputManager::catchInputEvents()
{
	sf::Event event;
	RawInputPack input;
	InputDivice divice = InputDivice::None;
	while (windowToManage->pollEvent(event))
	{
		if (event.type == sf::Event::EventType::KeyReleased || event.type == sf::Event::EventType::KeyPressed)
			divice = InputDivice::Keyboard;
		else if(event.type == sf::Event::EventType::MouseButtonPressed || event.type == sf::Event::EventType::MouseButtonReleased)
			divice = InputDivice::Mouse;
		// catch input on key pressed and released, ActionCommands settings will handle by itself when should it be activated (on key pressed or released)
		if (divice != InputDivice::None)
		{
			input.rawKeys.push_back({ (RawKeyCode)event.key.code, divice });
			input.mousePos = sf::Mouse::getPosition(*windowToManage);
		}
		// for test purpose (deallocation), delete later on
		else if (event.type == sf::Event::EventType::Closed)
			windowToManage->close();
		///////////////////////////////////////////////////////////////////////////
	}
	return std::move(input);
}

InputManager::ControllerButtons InputManager::rawInputToControllerButtonsInput(const RawInputPack & inputToTranslate)
{
	ControllerButtons controllerButtonsPressed;

	for (const auto & key : inputToTranslate.rawKeys)
	{
		if (key.inputDivice == InputDivice::Keyboard)
		{
			if (settings.keyBindings.keyboardBindings.count(key.keyCode))
				controllerButtonsPressed.push_back(settings.keyBindings.keyboardBindings[key.keyCode]);
		}
		else if (key.inputDivice == InputDivice::Mouse)
		{
			if (settings.keyBindings.mouseBindings.count(key.keyCode))
				controllerButtonsPressed.push_back(settings.keyBindings.mouseBindings[key.keyCode]);
		}
	}
	return std::move(controllerButtonsPressed);
}

