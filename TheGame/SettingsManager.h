#pragma once
#include <SFML\Graphics.hpp>
#include "Vec2.h"
#include <cstdint>

struct GraphicsSettings
{
	enum class Resolution : uint8_t
	{
		R1280x720,
		RCount
	};

	Resolution	resolution = Resolution(0);
	uint32_t	windowType = 7U;
	uint32_t	antialiasting = 0U;

	static const sf::Vector2u resolutions[uint8_t(Resolution::RCount)]; // "resolution" variable can be used as an index in this array
};

struct AudioSettings
{
	float_t generalVolume;
	float_t musicVolume;
	float_t abilitiesVolume;
	float_t communicationSoundsVolume;
};

enum class InputKeyAction : uint8_t
{
	MoveUp, MoveDown, MoveLeft, MoveRight,
	PrimaryAttack, secondaryAttack,
	FirstAbility, SecondAbility, ThridAbility, FourthAbility,
	InputsCount
};

class gameplaySettings
{
	// camera settings, etc...
};

class SettingsManager
{
public:

public:
	SettingsManager() = default;
	SettingsManager(const std::string & src);

	void			loadSettings(const std::string & src);
	void			saveSettings(const std::string & src);

	const wchar_t * getKeyBindings() const;

	void			bindKeyToAction(const InputKeyAction & action, wchar_t key);
	InputKeyAction	isKeyInUse(wchar_t key);

public:
	GraphicsSettings graphics;
	AudioSettings	 audio;

private:
	wchar_t			 keyBindings[(uint8_t)InputKeyAction::InputsCount];
};


