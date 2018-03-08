#include "stdInclude.h"
#include "InputManager.h"
#include "DisplayManager.h"
#include "Controller.h"



void RawInputReceiver::startUp(const std::shared_ptr<sf::RenderWindow> & windowPtr)
{
	windowToManage = windowPtr;
}

void RawInputReceiver::shoutDown()
{
	windowToManage.reset();
}

const RawInputPack & RawInputReceiver::catchInput()
{
	currentInput = RawInputPack();
	currentInput.mousePos = sf::Mouse::getPosition(*windowToManage);
	RawInputPack::RawKey key;
	sf::Event event;

	// catch input on key pressed and released, ActionCommands will handle by themselfs when should they be activated (on key pressed or released)
	while (windowToManage->pollEvent(event))
	{
		key.divice = InputDivice::None;


		if (event.type == sf::Event::EventType::KeyPressed || event.type == sf::Event::EventType::KeyReleased)
			key.divice = InputDivice::Keyboard;
		else if(event.type == sf::Event::EventType::MouseButtonPressed || event.type == sf::Event::EventType::MouseButtonReleased)
			key.divice = InputDivice::Mouse;

		if (key.divice != InputDivice::None)
		{
			if (event.type == sf::Event::EventType::KeyPressed || event.type == sf::Event::EventType::MouseButtonPressed)
				key.state = KeyState::Pressed;
			else if (event.type == sf::Event::EventType::KeyReleased || event.type == sf::Event::EventType::MouseButtonReleased)
				key.state = KeyState::Released;
			key.code = (RawKeyCode)event.key.code;

			currentInput.rawKeys.push_back(key);
		}
		// for test purpose (deallocation), delete later on (those kind of events should be handled by gui manager)
		else if (event.type == sf::Event::EventType::Closed)
			windowToManage->close();
		///////////////////////////////////////////////////////////////////////////
	}
	

	return currentInput;
}

const RawInputPack & RawInputReceiver::getCurrentInput() const
{
	return currentInput;
}
