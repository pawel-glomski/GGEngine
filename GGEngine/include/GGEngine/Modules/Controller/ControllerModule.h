#pragma once
#include <unordered_map>
#include "GGEngine/Modules/Input/InputModule.h"

struct ControllerComponent;

enum class ActionKey : uint8_t
{
	Num1, Num2, Num3, Num4, Num5,
	Options,
	Count
};

class ControllerModule : public Module<InputModule, WindowModule>
{

	using RawToActionMap_t = std::unordered_map<RawKey, ActionKey>;

	using ActionStateMap_t = std::unordered_map<ActionKey, KeyState>;

public:

	template<class ...MTypes>
	ControllerModule(const MDepPack_t<MTypes...> & dependencies);


	virtual void update() override;


	const RawToActionMap_t& getBindings() const;


	KeyState getActionKeyState(ActionKey actionKey) const;

	const Vec2f& getCursorWorldPosition() const;

	const Vec2f& getCursorWorldDeltaPosition() const;

private:

	void setBinding(const RawKey& raw, ActionKey action);

	void updateCursorState();

	void updateControllerState();

private:

	RawToActionMap_t bindings;

	ActionStateMap_t states;

	Vec2f cursorWorldPos;

	Vec2f cursorWorldDeltaPos;

};


template<class ...MTypes>
inline ControllerModule::ControllerModule(const MDepPack_t<MTypes...>& dependencies) : ModuleBase_t(dependencies)
{
	setBinding({ sf::Keyboard::Key::Num1, InputDivice::Keyboard }, ActionKey::Num1);
	setBinding({ sf::Keyboard::Key::Num2, InputDivice::Keyboard }, ActionKey::Num2);
	setBinding({ sf::Keyboard::Key::Num3, InputDivice::Keyboard }, ActionKey::Num3);
	setBinding({ sf::Keyboard::Key::Num4, InputDivice::Keyboard }, ActionKey::Num4);
	setBinding({ sf::Keyboard::Key::Num5, InputDivice::Keyboard }, ActionKey::Num5);

	setBinding({ sf::Keyboard::Key::Escape, InputDivice::Keyboard }, ActionKey::Options);
};