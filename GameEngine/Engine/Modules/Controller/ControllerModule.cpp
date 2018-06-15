#include "ControllerModule.h"
#include "Utilities/Math/Transform.h"

void ControllerModule::update()
{
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