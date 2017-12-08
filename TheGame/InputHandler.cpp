#include "pch.h"
#include "InputHandler.h"

void InputHandler::handleInputs(sf::RenderWindow & window, const wchar_t * keyBindings)
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		handleGameplayInput(event.key.code, keyBindings);
	}
}

void InputHandler::handleGameplayInput(wchar_t key, const wchar_t * keyBindings)
{
	GameplayInputResult();
}
