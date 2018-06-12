#pragma once
#include <unordered_map>
#include <array>
#include "InputModule.h"

struct ControllerComponent;

enum class ControllerAction : uint8_t
{
	MoveForward, MoveBackward, MoveLeft, MoveRight,
	PrimaryAttack, SecondaryAttack,
	FirstAbility, SecondAbility, ThridAbility, FourthAbility,
	Num1, Num2, Num3, Num4, Num5,
	Options,
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

	using KeyBindingsArray = std::array<RawInputPack::RawKey, (uint8_t)ControllerAction::Count>;

	using KeysStatesArray = std::array<std::unordered_map<RawKeyCode, KeyState>, (uint8_t)InputDivice::Count>;

public:

	template<class ...MTypes>
	ControllerModule(const MDepPack_t<MTypes...> & dependencies);


	virtual void update() override;

	const KeyBindingsArray& getBindings() const;

	const KeysStatesArray& getKeysStates() const;

private:

	void updateControllerState(const RawInputPack & rawInput);

private:

	// RawKey to ControllerAction bindings
	// ControllerAction members are used as indices here
	KeyBindingsArray bindings;	// move it to settings


	// divice-devided key bindings
	// InputDivice components are used as first indices (getting correct RawKeyCode-ControllerButton bindings for this divice)
	// RawKeyCode is used as second index (getting ControllerButton binded to this RawKeyCode)
	KeysStatesArray bindedKeysStates;

};


template<class ...MTypes>
inline ControllerModule::ControllerModule(const MDepPack_t<MTypes...>& dependencies) : ModuleBase_t(dependencies)
{

	bindings[(uint8_t)ControllerAction::PrimaryAttack] = RawInputPack::RawKey(sf::Mouse::Button::Left, InputDivice::Mouse);
	bindings[(uint8_t)ControllerAction::SecondaryAttack] = RawInputPack::RawKey(sf::Mouse::Button::Right, InputDivice::Mouse);


	bindings[(uint8_t)ControllerAction::MoveForward] = RawInputPack::RawKey(sf::Keyboard::Key::W, InputDivice::Keyboard);
	bindings[(uint8_t)ControllerAction::MoveBackward] = RawInputPack::RawKey(sf::Keyboard::Key::S, InputDivice::Keyboard);
	bindings[(uint8_t)ControllerAction::MoveLeft] = RawInputPack::RawKey(sf::Keyboard::Key::A, InputDivice::Keyboard);
	bindings[(uint8_t)ControllerAction::MoveRight] = RawInputPack::RawKey(sf::Keyboard::Key::D, InputDivice::Keyboard);
	bindings[(uint8_t)ControllerAction::FirstAbility] = RawInputPack::RawKey(sf::Keyboard::Key::Q, InputDivice::Keyboard);
	bindings[(uint8_t)ControllerAction::SecondAbility] = RawInputPack::RawKey(sf::Keyboard::Key::E, InputDivice::Keyboard);
	bindings[(uint8_t)ControllerAction::ThridAbility] = RawInputPack::RawKey(sf::Keyboard::Key::LControl, InputDivice::Keyboard);
	bindings[(uint8_t)ControllerAction::FourthAbility] = RawInputPack::RawKey(sf::Keyboard::Key::Space, InputDivice::Keyboard);

	bindings[(uint8_t)ControllerAction::Num1] = RawInputPack::RawKey(sf::Keyboard::Key::Num1, InputDivice::Keyboard);
	bindings[(uint8_t)ControllerAction::Num2] = RawInputPack::RawKey(sf::Keyboard::Key::Num2, InputDivice::Keyboard);
	bindings[(uint8_t)ControllerAction::Num3] = RawInputPack::RawKey(sf::Keyboard::Key::Num3, InputDivice::Keyboard);
	bindings[(uint8_t)ControllerAction::Num4] = RawInputPack::RawKey(sf::Keyboard::Key::Num4, InputDivice::Keyboard);
	bindings[(uint8_t)ControllerAction::Num5] = RawInputPack::RawKey(sf::Keyboard::Key::Num5, InputDivice::Keyboard);

	bindings[(uint8_t)ControllerAction::Options] = RawInputPack::RawKey(sf::Keyboard::Key::Escape, InputDivice::Keyboard);


	for (auto & bind : bindings)
		bindedKeysStates[(uint8_t)bind.divice][bind.code] = KeyState::Released;
};