#include "stdInclude.h"
#include "InputManager.h"

void InputManager::handleInput(sf::RenderWindow & window, const wchar_t * keyBindings)
{
	Input input = catchInputEvents(window);

	handleGuiInputs(input, window);
	handleGameplayInputs(input);
}

InputManager::Input InputManager::catchInputEvents(sf::RenderWindow & window)
{
	sf::Event event;
	Input input;

	while (window.pollEvent(event))
	{
		input.keyCode[input.count] = event.key.code;
		input.type[input.count] = event.type;
		input.count++;

		input.ctrl = event.key.control;
		input.alt = event.key.alt;
		input.shift = event.key.shift;
	}

	return input;
}

void InputManager::handleGameplayInputs(const Input & input)
{
}

void InputManager::handleGuiInputs(const Input & input, sf::RenderWindow & window)
{
	for (uint8_t i = 0; i < input.count; i++)
	{
		if (input.type[i] == sf::Event::Closed)
			window.close();
	}
}

