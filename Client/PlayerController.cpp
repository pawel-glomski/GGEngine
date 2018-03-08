#include "PlayerController.h"
#include "EntityManager.h"
#include "DisplayManager.h"

void PlayerController::startUp()
{
	auto & keyboardBindings = bindings[(uint8_t)InputDivice::Keyboard];
	auto & mouseBindings = bindings[(uint8_t)InputDivice::Keyboard];

	// rotate action has no key, its always reading current cursor position
	bindings[(uint8_t)ControllerAction::Rotate] = RawInputPack::RawKey(sf::Mouse::Button::ButtonCount, InputDivice::Mouse);

	bindings[(uint8_t)ControllerAction::MoveForward] = RawInputPack::RawKey(sf::Keyboard::Key::W, InputDivice::Keyboard);
	bindings[(uint8_t)ControllerAction::MoveBackward] = RawInputPack::RawKey(sf::Keyboard::Key::S, InputDivice::Keyboard);
	bindings[(uint8_t)ControllerAction::MoveLeft] = RawInputPack::RawKey(sf::Keyboard::Key::A, InputDivice::Keyboard);
	bindings[(uint8_t)ControllerAction::MoveRight] = RawInputPack::RawKey(sf::Keyboard::Key::D, InputDivice::Keyboard);
	bindings[(uint8_t)ControllerAction::FirstAbility] = RawInputPack::RawKey(sf::Keyboard::Key::Q, InputDivice::Keyboard);
	bindings[(uint8_t)ControllerAction::SecondAbility] = RawInputPack::RawKey(sf::Keyboard::Key::E, InputDivice::Keyboard);
	bindings[(uint8_t)ControllerAction::ThridAbility] = RawInputPack::RawKey(sf::Keyboard::Key::LControl, InputDivice::Keyboard);
	bindings[(uint8_t)ControllerAction::FourthAbility] = RawInputPack::RawKey(sf::Keyboard::Key::Space, InputDivice::Keyboard);

	bindings[(uint8_t)ControllerAction::PrimaryAttack] = RawInputPack::RawKey(sf::Mouse::Button::Left, InputDivice::Mouse);
	bindings[(uint8_t)ControllerAction::SecondaryAttack] = RawInputPack::RawKey(sf::Mouse::Button::Right, InputDivice::Mouse);

	for (auto & bind : bindings)
		bindedKeysStates[(uint8_t)bind.divice][bind.code] = KeyState::Released;
}
void PlayerController::shoutDown()
{
	for (auto & diviceKeyState: bindedKeysStates)
		diviceKeyState.clear();
	controlledEntity.reset();
}

void PlayerController::feedRawInput(const RawInputPack & rawInput)
{
	// set as HeldDown every keyState, that in previous tick was "Pressed"
	for (uint8_t i = 0; i < (uint8_t)ControllerAction::Count; i++)
		if (bindedKeysStates[(uint8_t)bindings[i].divice][bindings[i].code] == KeyState::Pressed)
			bindedKeysStates[(uint8_t)bindings[i].divice][bindings[i].code] = KeyState::HeldDown;

	for (const auto & key : rawInput.rawKeys)
		if (bindedKeysStates[(uint8_t)key.divice].count(key.code))
			bindedKeysStates[(uint8_t)key.divice][key.code] = key.state;

	ASSERT(!controlledEntity.expired(), "There is no controlled entity!");
	if (auto & mainEntity = controlledEntity.lock())
	{
		// give button states to controlled entity 
		mainEntity->getComponent<ControllerComponent>()->joystickRotation = angleBetweenVectors(Vec2f(1, 0), rawInput.signedCursorVector);
		mainEntity->getComponent<ControllerComponent>()->joystickPositionOffset = 
			Vec2f(rawInput.signedCursorVector.x * rawInput.windowSizeScale.x, rawInput.signedCursorVector.y * rawInput.windowSizeScale.y).length() / DisplaySettings::WorldToWindowRatio;
		
		auto & controllerButtonsStates = mainEntity->getComponent<ControllerComponent>()->controllerButtonStates;
		for (uint8_t i = 0; i < (uint8_t)ControllerAction::Count; i++)
			controllerButtonsStates[i] = bindedKeysStates[(uint8_t)bindings[i].divice][bindings[i].code];
	}
}

void PlayerController::setControlledEntity(const std::shared_ptr<Entity>& entity)
{
	ASSERT(entity, "Tried to set controlled entity to nullptr");
	ASSERT(entity->getComponent<ControllerComponent>(), "Tried to set controlled entity to entity that has no ControllerComponent");
	if(entity && entity->getComponent<ControllerComponent>())
		controlledEntity = entity;
}
