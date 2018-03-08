#pragma once
#include <unordered_map>
#include "RawInputReceiver.h"
#include "Array.h"
#include "Entity.h"

enum class ControllerAction : uint8_t
{
	Rotate, MoveForward, MoveBackward, MoveLeft, MoveRight,
	PrimaryAttack, SecondaryAttack,
	FirstAbility, SecondAbility, ThridAbility, FourthAbility,
	Count
};

struct ControllerButton
{
	ControllerAction action = ControllerAction::Count;
	KeyState keyState = KeyState::Released;

	ControllerButton(ControllerAction action) : action(action) {}
	ControllerButton() = default;
};

class PlayerController
{
public:

	void startUp();

	void shoutDown();

	void feedRawInput(const RawInputPack & rawInput);

	void setControlledEntity(const std::shared_ptr<Entity>& entity); 

private:

	// these are RawKey to ControllerAction bindings
	// ControllerAction members are used as indices here
	Array<RawInputPack::RawKey, (uint8_t)ControllerAction::Count> bindings;

	// divice-devided key bindings
	// InputDivice members are used as first indices (getting correct RawKeyCode-ControllerButton bindings for this divice)
	// RawKeyCode is used as second index (getting ControllerButton binded to this RawKeyCode)
	std::array<std::unordered_map<RawKeyCode, KeyState>, (uint8_t)InputDivice::Count> bindedKeysStates;

	std::weak_ptr<Entity> controlledEntity;
};