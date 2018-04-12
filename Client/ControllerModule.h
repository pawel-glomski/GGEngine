#pragma once
#include <unordered_map>
#include <array>
#include <memory>
#include "InputModule.h"
#include "Component.h"

struct ControllerComponent;

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



class ControllerModule : public Module<InputModule>
{

public:

	template<class ...MTypes>
	ControllerModule(const MDepPack_t<MTypes...> & dependencies);


	virtual void update(float_t dt);


	void setControlledEntity(const CPtr_t<ControllerComponent>& entityControllerC);


private:

	void updateControllerState(const RawInputPack & rawInput);

	void passControllerStateToEntity(const RawInputPack & rawInput);

private:

	// RawKey to ControllerAction bindings
	// ControllerAction members are used as indices here
	std::array<RawInputPack::RawKey, (uint8_t)ControllerAction::Count> bindings;	// move it to settings


	// divice-devided key bindings
	// InputDivice members are used as first indices (getting correct RawKeyCode-ControllerButton bindings for this divice)
	// RawKeyCode is used as second index (getting ControllerButton binded to this RawKeyCode)
	std::array<std::unordered_map<RawKeyCode, KeyState>, (uint8_t)InputDivice::Count> bindedKeysStates;


	std::weak_ptr<ControllerComponent> controlledEntityController;

};


template<class ...MTypes>
inline ControllerModule::ControllerModule(const MDepPack_t<MTypes...>& dependencies) : ModuleBase_t(dependencies)
{
	// rotate action has no key, its always set as HeldDown
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

	bindedKeysStates[(uint8_t)InputDivice::Mouse][sf::Mouse::Button::ButtonCount] = KeyState::HeldDown;
};