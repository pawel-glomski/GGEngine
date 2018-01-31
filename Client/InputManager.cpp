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

RawInputPack RawInputReceiver::catchRawInput()
{
	sf::Event event;
	RawInputPack input;
	InputDivice divice;

	// catch input on key pressed and released, ActionCommands will handle by themselfs when should they be activated (on key pressed or released)
	while (windowToManage->pollEvent(event))
	{
		divice = InputDivice::None;
		if (event.type == sf::Event::EventType::KeyReleased || event.type == sf::Event::EventType::KeyPressed)
			divice = InputDivice::Keyboard;
		else if(event.type == sf::Event::EventType::MouseButtonPressed || event.type == sf::Event::EventType::MouseButtonReleased)
			divice = InputDivice::Mouse;
		if (divice != InputDivice::None)
		{
			//std::cout << " " << event.key.code << std::endl;
			input.rawKeys.push_back({ (RawKeyCode)event.key.code, divice });
			input.mousePos = sf::Mouse::getPosition(*windowToManage);
		}
		// for test purpose (deallocation), delete later on (those kind of events should be handled by gui manager)
		else if (event.type == sf::Event::EventType::Closed)
			windowToManage->close();
		///////////////////////////////////////////////////////////////////////////
	}
	//std::cout << input.rawKeys.currentSize() << std::endl;
	return input;
}
