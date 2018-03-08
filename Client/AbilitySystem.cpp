#include "AbilitySystem.h"
#include "EntityManager.h"

AbilitySystem::AbilitySystem()
{
	usesEveryEntity = false;
}

void AbilitySystem::update(EntityManager & entityManager, float_t dt)
{
	if (entitiesToUpdate)
		for (auto & entityNode : *entitiesToUpdate)
		{
			auto & entity = *entityNode.second;

			auto & abilities = entity.getComponent<AbilityComponent>()->executingAbilities;
			auto & abilitySet = entity.getComponent<AbilityComponent>()->abilitySet;
			auto & buttonStates = entity.getComponent<ControllerComponent>()->controllerButtonStates;

			for (uint8_t i = 0; i < (uint8_t)ControllerAction::Count; i++)
				if (buttonStates[i] == KeyState::Pressed && !abilities.count(abilitySet[i]))
					abilities[abilitySet[i]] = abilitySet[i]->makeInstance();
				else if (buttonStates[i] == KeyState::Released && abilities.count(abilitySet[i]))
					abilities[abilitySet[i]]->endInputDependendStage();

			for (auto actIt = abilities.begin(); actIt != abilities.end(); )
				if (actIt->second->execute(entityManager, entity, dt))
					actIt = abilities.erase(actIt);
				else
					actIt++;
		}
}

void AbilitySystem::addEntity(const EntityManager::EntityPtr & entity, const std::shared_ptr<EntityManager::EntityContainer>& everyEntityContainer)
{
	if (entity->getComponent<AbilityComponent>() && entity->getComponent<ControllerComponent>())
		EntityUpdateSystem::addEntity(entity, everyEntityContainer);
}
