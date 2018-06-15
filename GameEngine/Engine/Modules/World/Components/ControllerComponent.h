#pragma once
#include <array>
#include <ECSpp/Component.h>
#include "InputModule.h"
#include "ControllerModule.h"

// ControllerAction members are indices in this array 
typedef std::array<KeyState, (uint8_t)ActionKey::Count> ControllerKeyContainer;

struct ControllerComponent : public epp::Component
{
	ControllerComponent()
	{
		for (uint8_t i = 0; i < (uint8_t)ActionKey::Count; i++)
			keysStates[i] = KeyState::Released;
	}

	float_t joystickRotation = 0;		// angle between [1,0] vector and vector from window center to cursor

	float_t joystickPositionOffset = 0;	// length of vector from window's center to cursor

	ControllerKeyContainer keysStates;	// ControllerAction members are indices in this array 
};