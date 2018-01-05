#pragma once
#include "Vec2.h"
#include <SFML/Graphics.hpp>
#include "SettingsManager.h"

class InputManager
{
public:
	struct Input
	{
		static const uint8_t maxInputs = 6;

		uint8_t count = 0;
		wchar_t keyCode[maxInputs] = {};
		uint8_t type[maxInputs] = {};

		bool ctrl = false;
		bool alt = false;
		bool shift = false;

		//Vect2u mousePos;
	};

public:
	void handleInput(sf::RenderWindow & window, const wchar_t * keyBindings);

private:
	Input catchInputEvents(sf::RenderWindow & window);

	void handleGameplayInputs(const Input & input);
	void handleGuiInputs(const Input & input, sf::RenderWindow & window);

private:
};

