#pragma once
#include <array>
#include "WindowModule.h"

enum class InputDivice : uint8_t 
{ Keyboard, Mouse, Count };

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
		RawKey() = default;

		RawKey(RawKeyCode keyCode, InputDivice inputDivice) : code(keyCode), divice(inputDivice) {};

		RawKeyCode code = -1;
		KeyState state = KeyState::Released;
		InputDivice divice = InputDivice::Keyboard;
	};


	void resetKeys()
	{
		rawKeys = std::array<RawKey, maxInput>();
	}


	static const uint8_t maxInput = 6;

	std::array<RawKey, maxInput> rawKeys;

	Vec2f absCursorPos;	// position of a cursor on a window <0; winSize>
	Vec2f signedCursorVec;	// vector from window's center to cursor <-winSize / 2; winSize / 2f>
	Vec2f cursorPosChange;
};



class InputModule : public Module<WindowModule>
{
public:
	
	template<class ...MTypes>
	InputModule(const MDepPack_t<MTypes...> & dependencies) : ModuleBase_t(dependencies) {}


	virtual void update() override;


	const RawInputPack & getCurrentInput() const;


private:

	void assignMousePosition();
	void assignInputKeys();


private:

	RawInputPack currentInput;
};

