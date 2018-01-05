#include "stdInclude.h"
#include "SettingsManager.h"

const sf::Vector2u GraphicsSettings::resolutions[uint8_t(Resolution::RCount)] =
{ 
	{1280, 720}
};


SettingsManager::SettingsManager(const std::string & src)
{
	loadSettings(src);
}

void SettingsManager::loadSettings(const std::string & src)
{
	//...
}

void SettingsManager::saveSettings(const std::string & src)
{
	//...
}

const wchar_t* SettingsManager::getKeyBindings() const
{
	return keyBindings;
}

void SettingsManager::bindKeyToAction(const InputKeyAction & action, wchar_t key)
{
	keyBindings[uint8_t(action)] = key;
}

InputKeyAction SettingsManager::isKeyInUse(wchar_t key)
{
	for (uint8_t i = 0; i < uint8_t(InputKeyAction::InputsCount); i++)
		if (keyBindings[i] == key)
			return InputKeyAction(i);

	return InputKeyAction::InputsCount;
}