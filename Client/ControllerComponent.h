#pragma once
#include <array>
#include "Component.h"
#include "RawInputReceiver.h"
#include "Array.h"
#include "PlayerController.h"


// ControllerAction members are indices in this array 
typedef std::array<KeyState, (uint8_t)ControllerAction::Count> ControllerButtonContainer;

struct ControllerComponent : public Component
{
	ControllerComponent();

	float_t joystickRotation;		// angle between [1,0] vector and vector from window center to cursor

	float_t joystickPositionOffset;	// length of a vector from window's center to cursor

	ControllerButtonContainer controllerButtonStates;	// ControllerAction members are indices in this array 
};