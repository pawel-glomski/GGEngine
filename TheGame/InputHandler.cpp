#include "pch.h"
#include "InputHandler.h"

void InputHandler::handleInput(sf::RenderWindow & window, const wchar_t * keyBindings)
{
	Input input = catchInputEvents(window);

	handleGuiInputs(input);
	handleGameplayInputs(input);
}

InputHandler::Input InputHandler::catchInputEvents(sf::RenderWindow & window)
{
	sf::Event event;
	Input input;

	while (window.pollEvent(event))
	{
		input.ctrl = event.key.control;
		input.alt = event.key.alt;
		input.shift = event.key.shift;
		

	}
}

void InputHandler::handleGameplayInputs(const Input & input)
{
}

void InputHandler::handleGuiInputs(const Input & input)
{
}

