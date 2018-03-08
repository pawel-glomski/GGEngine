#pragma once
#include "EntityUpdateSystem.h"
#include "AbilityComponent.h"
#include "TransformComponent.h"
#include "ControllerComponent.h"

class AbilitySystem : public EntityUpdateSystem
{
public:

	AbilitySystem();

	virtual void update(EntityManager & entityManager, float_t dt) override;

	virtual void addEntity(const EntityManager::EntityPtr & entity, const std::shared_ptr<EntityManager::EntityContainer> & everyEntityContainer) override;
};

