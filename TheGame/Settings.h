#pragma once

class Settings
{
public:

	struct AudioSettings
	{
		// ...
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
	Settings(const std::string & settingsPath);

private:
	//GraphicsSettings	graphics;
	AudioSettings		audio;
	wchar_t keyBindings[(uint8_t)InputKeyAction::InputsCount];
};

