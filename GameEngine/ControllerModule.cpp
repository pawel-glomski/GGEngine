#include "ControllerModule.h"
#include "WindowModule.h"
#include "Transform.h"

void ControllerModule::update()
{
	const RawInputPack & rawInput = getDependency<InputModule>().getCurrentInput();
	updateControllerState(rawInput);
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
