#pragma once
#include "Settings.h"

class InputHandler
{
public:
	struct Input
	{
		static const uint8_t maxKeysDown = 6;

		wchar_t keyCode[maxKeysDown];

		bool ctrl;
		bool alt;
		bool shift;

		uint16_t mousePosX;
		uint16_t mousePosY;
	};

public:
	void handleInput(sf::RenderWindow & window, const wchar_t * keyBindings);

private:
	Input catchInputEvents(sf::RenderWindow & window);

	void handleGameplayInputs(const Input & input);
	void handleGuiInputs(const Input & input);

private:
};

