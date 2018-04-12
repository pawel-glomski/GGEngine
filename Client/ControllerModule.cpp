#include "ControllerModule.h"
#include "ControllerComponent.h"
#include "WindowModule.h"
#include "Transform.h"

void ControllerModule::update(float_t dt)
{
	const RawInputPack & rawInput = getDependency<InputModule>().getCurrentInput();
	updateControllerState(rawInput);
	passControllerStateToEntity(rawInput);
}

void ControllerModule::updateControllerState(const RawInputPack & rawInput)
{
	// set as HeldDown every keyState, that in previous tick was "Pressed"
	for (uint8_t i = 0; i < (uint8_t)ControllerAction::Count; i++)
		if (bindedKeysStates[(uint8_t)bindings[i].divice][bindings[i].code] == KeyState::Pressed)
			bindedKeysStates[(uint8_t)bindings[i].divice][bindings[i].code] = KeyState::HeldDown;


	for (const auto & key : rawInput.rawKeys)
		if (bindedKeysStates[(uint8_t)key.divice].count(key.code))
			bindedKeysStates[(uint8_t)key.divice][key.code] = key.state;
}

void ControllerModule::passControllerStateToEntity(const RawInputPack & rawInput)
{
	ASSERT(!controlledEntityController.expired(), "No entity is being controlled !");
	if (auto & controller = controlledEntityController.lock())
	{
		controller->joystickRotation = angleBetweenVectors(Vec2f(1, 0) * asRotationMatrix(-PI_F / 2.f), rawInput.signedCursorVector);
		controller->joystickPositionOffset = rawInput.signedCursorVector.length() / Settings<WindowModule>::WorldToViewRatio;

		auto & controllerButtonsStates = controller->keysStates;
		for (uint8_t i = 0; i < (uint8_t)ControllerAction::Count; i++)
			controllerButtonsStates[i] = bindedKeysStates[(uint8_t)bindings[i].divice][bindings[i].code];
	}
}


void ControllerModule::setControlledEntity(const CPtr_t<ControllerComponent>& entityControllerC)
{
	ASSERT(entityControllerC, "Tried to set controlled entity to nullptr");
	if (entityControllerC)
		controlledEntityController = entityControllerC;
}



