#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Vec2.h"
#include "ActionCommand.h"
#include "Array.h"

enum class InputDivice : uint8_t { None, Keyboard, Mouse };
typedef int8_t RawKeyCode;

struct RawInputPack
{
	struct RawKey
	{
		RawKeyCode code = sf::Keyboard::Key::Unknown;
		InputDivice inputDivice = InputDivice::None;
		RawKey() = default;
		RawKey(RawKeyCode keyCode, InputDivice inputDivice) : code(keyCode), inputDivice(inputDivice) {};
	};

	static const uint8_t maxInput = 10;

	Array<RawKey, maxInput> rawKeys;
	Vect2u mousePos;
};

class RawInputReceiver
{
public:
	void startUp(const std::shared_ptr<sf::RenderWindow> & windowPtr);
	void shoutDown();

	RawInputPack catchRawInput();

private:
	std::shared_ptr<sf::RenderWindow> windowToManage;
};

