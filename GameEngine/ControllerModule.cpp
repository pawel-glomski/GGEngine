#include "ControllerModule.h"
#include "Transform.h"


void ControllerModule::update()
{
	response();
	updateControllerState();
	updateCursorState();
}

void ControllerModule::setBinding(const RawKey & raw, ActionKey action)
{
	bindings[raw] = action;
	states[action] = KeyState::Released;
}

void ControllerModule::updateCursorState()
{
	cursorWorldPos = getDependency<InputModule>().getCurrentInput().signedCursorPos + asVec<Vec2f>(getDependency<WindowModule>().getWin().getView().getCenter());
	cursorWorldPos /= Settings<WindowModule>::WorldToViewRatio;
	cursorWorldDeltaPos = getDependency<InputModule>().getCurrentInput().cursorDeltaPos;
	cursorWorldDeltaPos /= Settings<WindowModule>::WorldToViewRatio;
}

void ControllerModule::updateControllerState()
{
	const RawInputPack& rawInput = getDependency<InputModule>().getCurrentInput();

	// set as HeldDown every keyState, that in previous tick was "Pressed"
	for (auto& stateNode : states)
		if (stateNode.second == KeyState::Pressed)
			stateNode.second = KeyState::HeldDown;

	for (const auto & key : rawInput.rawKeys)
		if (auto found = bindings.find(key); found != bindings.end())
			states[found->second] = key.state;
}

void ControllerModule::response()
{
	{
		sf::View view = getDependency<WindowModule>().getWin().getView();

		if (getActionKeyState(ActionKey::MoveUp) != KeyState::Released)
			view.setCenter(view.getCenter() + sf::Vector2f(0.f, -0.1f) * Settings<WindowModule>::WorldToViewRatio);
		if (getActionKeyState(ActionKey::MoveDown) != KeyState::Released)
			view.setCenter(view.getCenter() + sf::Vector2f(0, 0.1f) * Settings<WindowModule>::WorldToViewRatio);
		if (getActionKeyState(ActionKey::MoveLeft) != KeyState::Released)
			view.setCenter(view.getCenter() + sf::Vector2f(-0.1f, 0.f) * Settings<WindowModule>::WorldToViewRatio);
		if (getActionKeyState(ActionKey::MoveRight) != KeyState::Released)
			view.setCenter(view.getCenter() + sf::Vector2f(0.1f, 0.f) * Settings<WindowModule>::WorldToViewRatio);

		if (getActionKeyState(ActionKey::ZoomIn) != KeyState::Released)
			view.setSize(view.getSize() / 1.01f);
		if (getActionKeyState(ActionKey::ZoomOut) != KeyState::Released)
			view.setSize(view.getSize() * 1.01f);

		getDependency<WindowModule>().getWin().setView(view);
	}
}


const ControllerModule::RawToActionMap & ControllerModule::getBindings() const
{
	return bindings;
}

KeyState ControllerModule::getActionKeyState(ActionKey actionKey) const
{
	return states.at(actionKey);
}

const Vec2f & ControllerModule::getCursorWorldPosition() const
{
	return cursorWorldPos;
}

const Vec2f & ControllerModule::getCursorWorldDeltaPosition() const
{
	return cursorWorldDeltaPos;
}