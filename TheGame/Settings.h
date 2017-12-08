#pragma once

class Settings
{
public:

	struct GraphicsSettings
	{
		size_t resolutionX = 1000;
		size_t resolutionY = 600;
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

public:
	Settings() = default;
	Settings(const std::string & src);

	void			loadSettings(const std::string & src);
	void			saveSettings(const std::string & src);

	const wchar_t * getKeyBindings() const;
	void			bindKeyToAction(const InputKeyAction & action, wchar_t key);
	InputKeyAction	isKeyInUse(wchar_t key);

	GraphicsSettings	graphics;
	AudioSettings		audio;

private:
	wchar_t				keyBindings[(uint8_t)InputKeyAction::InputsCount];
};

