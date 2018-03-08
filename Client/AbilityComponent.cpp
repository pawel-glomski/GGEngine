#include "AbilityComponent.h"

AbilityComponent::AbilityComponent()
{
	abilitySet[0] = RotateAbility().getStaticInstance();
	executingAbilities[abilitySet[0]] = abilitySet[0]->makeInstance();

	for (uint8_t i = 1; i < (uint8_t)ControllerAction::Count; i++)
		abilitySet[i] = UndefinedAbility().getStaticInstance(); //  - no action command
}
