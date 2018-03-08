#include "stdInclude.h"
#include "RawInputReceiver.h"
#include "DisplayManager.h"

void setInputDivice(RawInputPack::RawKey & key, const sf::Event & event);

void setKeyState(RawInputPack::RawKey & key, const sf::Event & event);

void RawInputReceiver::catchInput(const std::shared_ptr<sf::RenderWindow>& window)
{
	currentInput = RawInputPack();
	currentInput.absCursorPosition = sf::Mouse::getPosition(*window);
	currentInput.signedCursorVector = currentInput.absCursorPosition - Vec2f(window->getSize()) / 2.f;
	currentInput.windowSizeScale = Vec2f(DisplaySettings::ViewResolution.x / window->getSize().x, DisplaySettings::ViewResolution.y / window->getSize().y);

	RawInputPack::RawKey key;
	sf::Event event;

	while (window->pollEvent(event))
	{
		setInputDivice(key, event);
		if (key.divice != InputDivice::Count)
		{
			key.code = (RawKeyCode)event.key.code;
			setKeyState(key, event);

			currentInput.rawKeys.push_back(key);
		}
		// for test purpose (deallocation), delete later on (window events should be handled by gui manager)
		else if (event.type == sf::Event::EventType::Closed)
			window->close();
		///////////////////////////////////////////////////////////////////////////
	}
}

const RawInputPack & RawInputReceiver::getCurrentInput() const
{
	return currentInput;
}

void setInputDivice(RawInputPack::RawKey & key, const sf::Event & event)
{
	if (event.type == sf::Event::EventType::KeyPressed || event.type == sf::Event::EventType::KeyReleased)
		key.divice = InputDivice::Keyboard;
	else if (event.type == sf::Event::EventType::MouseButtonPressed || event.type == sf::Event::EventType::MouseButtonReleased)
		key.divice = InputDivice::Mouse;
	else
		key.divice = InputDivice::Count;
}

void setKeyState(RawInputPack::RawKey & key, const sf::Event & event)
{
	if (event.type == sf::Event::EventType::KeyPressed || event.type == sf::Event::EventType::MouseButtonPressed)
		key.state = KeyState::Pressed;
	else if (event.type == sf::Event::EventType::KeyReleased || event.type == sf::Event::EventType::MouseButtonReleased)
		key.state = KeyState::Released;
}


