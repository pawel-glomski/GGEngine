#include "stdInclude.h"
#include "InputManager.h"
#include "DisplayManager.h"
#include "Controller.h"

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
	windowToManage = windowPtr;
}

void InputManager::shoutDown()
{
	windowToManage.reset();
}

void InputManager::setInputTargetController(Controller * controller)
{
	ASSERT(controller, "Tried to set nullptr controller");
	if(controller)
		inputTargetController = controller;
}

void InputManager::bindKeyToControllerButton(const InputSettings::ControllerButton & action, uint8_t key, uint8_t type)
{
	ASSERT(((type == sf::Event::EventType::KeyReleased) || (type == sf::Event::EventType::KeyReleased)),
		"Wrong event type passed. Only KeyReleased or MouseButtonReleased are acceptable.");

	if (type == sf::Event::EventType::KeyReleased)
		settings.keyBindings.keyboardBindings[key] = action;
	else if(type == sf::Event::EventType::MouseButtonReleased)
		settings.keyBindings.mouseBindings[key] = action;
}

InputManager::ControllerButtonsVector InputManager::handleInput()
{
	RawInputPack inputToTranslate = catchInputEvents();
	ControllerButtonsVector controllerButtonInputForm;

	for (const auto & key : inputToTranslate.rawKeys)
	{
		if (key.second == sf::Event::EventType::KeyReleased || key.second == sf::Event::EventType::KeyPressed)
		{
			if(settings.keyBindings.keyboardBindings.count(key.first))
				controllerButtonInputForm.push_back(settings.keyBindings.keyboardBindings.at(key.first));
			
		}
		else if (key.second == sf::Event::EventType::MouseButtonReleased)
		{
			if (settings.keyBindings.mouseBindings.count(key.first))
				controllerButtonInputForm.push_back(settings.keyBindings.mouseBindings.at(key.first));
		}
	}

	return controllerButtonInputForm;
}

InputManager::RawInputPack InputManager::catchInputEvents()
{
	sf::Event event;
	RawInputPack input;

	while (windowToManage->pollEvent(event))
	{
		if (event.type == sf::Event::EventType::KeyReleased || event.type == sf::Event::EventType::MouseButtonReleased || event.type == sf::Event::EventType::KeyPressed)
		{
			input.rawKeys.push_back({ event.key.code, event.type });

			input.ctrl = event.key.control;
			input.alt = event.key.alt;
			input.shift = event.key.shift;
			input.mousePos = sf::Mouse::getPosition(*windowToManage);
		}
		// for test purpose (deallocation), delete later on
		else if (event.type == sf::Event::EventType::Closed)
			windowToManage->close();
		///////////////////////////////////////////////////////////////////////////
	}

	return std::move(input);
}