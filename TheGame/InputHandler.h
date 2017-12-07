#pragma once
#include "Settings.h"

class InputHandler
{
public:
	class GameplayInputResult
	{
		unsigned int dirToMouseX;
		unsigned int dirToMouseY;
		Settings::InputKeyAction lastTwoActions[2];
	};


public:
	GameplayInputResult handleGameplayInput(const wchar_t keyBindings[(unsigned int)Settings::InputKeyAction::InputsCount]);
	void				handleClientInput();

};

