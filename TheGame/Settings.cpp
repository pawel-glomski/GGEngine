#include "pch.h"
#include "Settings.h"


Settings::Settings(const std::string & src)
{
	loadSettings(src);
}

void Settings::loadSettings(const std::string & src)
{
}

void Settings::saveSettings(const std::string & src)
{
}

const wchar_t * Settings::getKeyBindings() const
{
	return keyBindings;
}

void Settings::bindKeyToAction(const InputKeyAction & action, wchar_t key)
{
	keyBindings[uint8_t(action)] = key;
}

Settings::InputKeyAction Settings::isKeyInUse(wchar_t key)
{
	for (uint8_t i = 0; i < uint8_t(InputKeyAction::InputsCount); i++)
		if (keyBindings[i] == key)
			return InputKeyAction(i);

	return InputKeyAction::InputsCount;
}
