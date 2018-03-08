#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Vec2.h"
#include "Array.h"

enum class InputDivice : uint8_t { Keyboard, Mouse, Count };

enum class KeyState : uint8_t 
{
	Pressed,	// when key is pressed for the first time
	HeldDown,	// when key is pressed for more than one tick
	Released	// when key is released
};

using RawKeyCode = int8_t;

struct RawInputPack
{
	struct RawKey
	{
		RawKeyCode code = -1;
		KeyState state = KeyState::Released;
		InputDivice divice = InputDivice::Count;
		RawKey() = default;
		RawKey(RawKeyCode keyCode, InputDivice inputDivice) : code(keyCode), divice(inputDivice) {};
	};

	static const uint8_t maxInput = 10;

	Array<RawKey, maxInput> rawKeys;

	Vec2f absCursorPosition;	// position of a cursor on a window <0; winSize> if mouse is in window
	Vec2f signedCursorVector;	// vector from window's center to cursor <-winSize / 2; winSize / 2f>
	Vec2f windowSizeScale;		// scale of ViewResolution to current window size
};

class RawInputReceiver
{
public:

	void catchInput(const std::shared_ptr<sf::RenderWindow> & window);

	const RawInputPack & getCurrentInput() const;

private:

	RawInputPack currentInput;
};