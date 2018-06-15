#pragma once
#include <array>
#include "Modules/Window/WindowModule.h"
#include "RawKey.h"



struct RawInputPack
{
	void resetKeys()
	{
		rawKeys = std::array<RawKey, maxInput>();
	}


	static const uint8_t maxInput = 6;

	std::array<RawKey, maxInput> rawKeys;

	Vec2f absCursorPos;	// position of a cursor on a window <0; winSize>
	Vec2f signedCursorPos;	// vector from window's center to cursor <-winSize / 2; winSize / 2>
	Vec2f cursorDeltaPos;
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

