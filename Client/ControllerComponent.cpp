#include "ControllerComponent.h"

ControllerComponent::ControllerComponent()
{
	for (uint8_t i = 0; i < (uint8_t)ControllerAction::Count; i++)
		controllerButtonStates[i] = KeyState::Released;
}
