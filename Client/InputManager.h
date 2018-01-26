#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>
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

	struct KeyBindings
	{
		typedef int8_t RawKeyCode;
		typedef std::unordered_map<RawKeyCode, ControllerButton> ControllerButtonsBindings;

		// default keyBindings
		KeyBindings();

		ControllerButtonsBindings keyboardBindings;
		ControllerButtonsBindings mouseBindings;
	};

	typedef std::unordered_map<ControllerButton, ActionCommand*> ActionsSet;

public:

	KeyBindings keyBindings;
	ActionsSet actionsSet;	// player-chosen skills
};

// Gathers input and ControllerButton it to ActionOrders and then to ActionCommands using KeyBindings
class InputManager
{
	typedef std::vector<InputSettings::ControllerButton> ControllerButtonsVector;

public:
	struct RawInputPack
	{
		typedef InputSettings::KeyBindings::RawKeyCode RawKeyCode, RawKeyType;
		typedef std::vector<std::pair<RawKeyCode, RawKeyType>> RawKeysVector;

		RawKeysVector rawKeys = RawKeysVector(6);

		bool ctrl = false;
		bool alt = false;
		bool shift = false;
		
		Vect2u mousePos;
	};

public:
	void startUp(const std::shared_ptr<sf::RenderWindow> & windowPtr);
	void shoutDown();

	void setInputTargetController(Controller * controller);

	ControllerButtonsVector handleInput();

	void bindKeyToControllerButton(const InputSettings::ControllerButton & action, uint8_t key, uint8_t type);
private:
	RawInputPack catchInputEvents();

private:
	InputSettings settings;

	std::shared_ptr<sf::RenderWindow> windowToManage;
	Controller* inputTargetController;
};

