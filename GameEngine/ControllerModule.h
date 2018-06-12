#pragma once
#include <unordered_map>
#include <array>
#include "InputModule.h"

struct ControllerComponent;

enum class ActionKey : uint8_t
{
	MoveForward, MoveBackward, MoveLeft, MoveRight,
	ZoomIn, ZoomOut,
	LMB, RMB,
	Num1, Num2, Num3, Num4, Num5,
	Options,
	Count
};

class ControllerModule : public Module<InputModule, WindowModule>
{

	using RawToActionMap = spp::sparse_hash_map<RawKey, ActionKey>;

	using ActionStateMap = spp::sparse_hash_map<ActionKey, KeyState>;

public:

	template<class ...MTypes>
	ControllerModule(const MDepPack_t<MTypes...> & dependencies);


	virtual void update() override;


	const RawToActionMap& getBindings() const;


	KeyState getActionKeyState(ActionKey actionKey);

private:

	void setBinding(const RawKey& raw, ActionKey action);

	void updateControllerState();

	void response();

private:

	RawToActionMap bindings;

	ActionStateMap states;

};


template<class ...MTypes>
inline ControllerModule::ControllerModule(const MDepPack_t<MTypes...>& dependencies) : ModuleBase_t(dependencies)
{
	setBinding({ sf::Mouse::Button::Left, InputDivice::Mouse }, ActionKey::LMB);
	setBinding({ sf::Mouse::Button::Right, InputDivice::Mouse }, ActionKey::RMB);

	setBinding({ sf::Keyboard::Key::W, InputDivice::Keyboard }, ActionKey::MoveForward);
	setBinding({ sf::Keyboard::Key::S, InputDivice::Keyboard }, ActionKey::MoveBackward);
	setBinding({ sf::Keyboard::Key::A, InputDivice::Keyboard }, ActionKey::MoveLeft);
	setBinding({ sf::Keyboard::Key::D, InputDivice::Keyboard }, ActionKey::MoveRight);

	setBinding({ sf::Keyboard::Key::LControl, InputDivice::Keyboard }, ActionKey::ZoomIn);
	setBinding({ sf::Keyboard::Key::Space, InputDivice::Keyboard }, ActionKey::ZoomOut);

	setBinding({ sf::Keyboard::Key::Num1, InputDivice::Keyboard }, ActionKey::Num1);
	setBinding({ sf::Keyboard::Key::Num2, InputDivice::Keyboard }, ActionKey::Num2);
	setBinding({ sf::Keyboard::Key::Num3, InputDivice::Keyboard }, ActionKey::Num3);
	setBinding({ sf::Keyboard::Key::Num4, InputDivice::Keyboard }, ActionKey::Num4);
	setBinding({ sf::Keyboard::Key::Num5, InputDivice::Keyboard }, ActionKey::Num5);

	setBinding({ sf::Keyboard::Key::Escape, InputDivice::Keyboard }, ActionKey::Options);
};