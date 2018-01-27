#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>
#include "Vec2.h"
#include "Singleton.h"
#include "ActionCommand.h"

class Controller;

struct InputSettings
{
public:

	enum class ControllerButton : uint8_t
	{
		MoveForward, MoveBackward, MoveLeft, MoveRight,
		PrimaryAttack, SecondaryAttack,
		FirstAbility, SecondAbility, ThridAbility, FourthAbility,
		Count
	};

	typedef std::unordered_map<ControllerButton, ActionCommand*> ActionsSet;

	struct KeyBindings
	{
		
		typedef int8_t RawKeyCode;
		
		typedef std::unordered_map<RawKeyCode, ControllerButton> ControllerButtonsBindings;

		// default keyBindings
		KeyBindings();

		ControllerButtonsBindings keyboardBindings;
		ControllerButtonsBindings mouseBindings;
	};

public:
	void startUp();
	void shoutDown();

public:

	KeyBindings keyBindings;
	ActionsSet actionsSet;	// player-chosen skills
};

// Gathers input and ControllerButton it to ActionOrders and then to ActionCommands using KeyBindings
class InputManager
{
	typedef std::vector<InputSettings::ControllerButton> ControllerButtons;
	typedef std::vector<ActionCommand*> ActionCommands;
	typedef InputSettings::KeyBindings::RawKeyCode RawKeyCode;

public:
	enum class InputDivice : uint8_t { None, Keyboard, Mouse };

	struct RawInputPack
	{
		struct RawKey
		{
			RawKeyCode keyCode = sf::Keyboard::Key::Unknown;
			InputDivice inputDivice = InputDivice::None;
			RawKey() = default;
			RawKey(RawKeyCode keyCode, InputDivice inputDivice) : keyCode(keyCode), inputDivice(inputDivice) {};
		};
		std::vector<RawKey> rawKeys = std::vector<RawKey>(6);
		Vect2u mousePos;
	};

public:
	void startUp(const std::shared_ptr<sf::RenderWindow> & windowPtr);
	void shoutDown();

	void setInputTargetController(Controller * controller);

	ActionCommands handleGameplayInput();

	void bindKeyToControllerButton(const InputSettings::ControllerButton & action, RawKeyCode key, InputDivice inputDivice);
private:
	RawInputPack		catchInputEvents();
	ControllerButtons	rawInputToControllerButtonsInput(const RawInputPack & inputToTranslate);

private:
	InputSettings settings;
	Controller* inputTargetController;
	std::shared_ptr<sf::RenderWindow> windowToManage;

};

