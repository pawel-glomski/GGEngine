#pragma once
#include <unordered_map>
#include "Ability.h"
#include <array>
#include "PlayerController.h"

// every entity has its own abilitySet
struct AbilityComponent :
	public Component
{
	// Array of static Ability instances assigned to certain controller buttons, these instances enable creating instances of correct type without knowing the type
	// through virtual function: makeInstance (used by AbilitySystem)
	// ControllerAction values works as indices here.
	std::array<const Ability*, (uint8_t)ControllerAction::Count> abilitySet;

	// map of currently executing abilitys, where key is address of static ability instance 
	// and value is pointer to instance returned by makeInstance function called on that static instance
	std::unordered_map<const Ability*, std::unique_ptr<Ability>> executingAbilities;

	AbilityComponent();
};