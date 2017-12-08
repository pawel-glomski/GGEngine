#pragma once
#include "Settings.h"

class InputHandler
{
public:
	class GameplayInputResult
	{
		unsigned int dirToMouseX;
		unsigned int dirToMouseY;
		Settings::InputKeyAction action;
	};

public:
	void handleInputs(sf::RenderWindow & window, const wchar_t * keyBindings);

private:
	void handleGameplayInput(wchar_t key, const wchar_t * keyBindings);
	void handleClientInput();
};

