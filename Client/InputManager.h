#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Vec2.h"
#include "ActionCommand.h"
#include "Array.h"
#include "Singleton.h"

enum class InputDivice : uint8_t { None, Keyboard, Mouse };
enum class KeyState : uint8_t { Pressed, Released };
typedef int8_t RawKeyCode;

struct RawInputPack
{
	struct RawKey
	{
		RawKeyCode code = sf::Keyboard::Key::Unknown;
		KeyState state = KeyState::Pressed;
		InputDivice divice = InputDivice::None;
		RawKey() = default;
		RawKey(RawKeyCode keyCode, KeyState state, InputDivice inputDivice) : code(keyCode), state(state), divice(inputDivice) {};
	};

	static const uint8_t maxInput = 10;
	Array<RawKey, maxInput> rawKeys;
	Vect2f mousePos;
};

class RawInputReceiver : public Singleton<RawInputReceiver>
{
	friend class Singleton<RawInputReceiver>;
public:
	void startUp(const std::shared_ptr<sf::RenderWindow> & windowPtr);
	void shoutDown();

	const RawInputPack & catchInput();
	const RawInputPack & getCurrentInput() const;

private:
	RawInputReceiver() = default;

private:
	std::shared_ptr<sf::RenderWindow> windowToManage;
	RawInputPack currentInput;
};

