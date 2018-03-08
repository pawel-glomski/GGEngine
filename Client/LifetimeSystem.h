#pragma once
#include "EntityUpdateSystem.h"
#include "LifetimeComponent.h"

class LifetimeSystem : 
	public EntityUpdateSystem
{
public:

	LifetimeSystem();

	virtual void update(EntityManager & entityManager, float_t dt) override;

	virtual void addEntity(const EntityManager::EntityPtr & entity, const std::shared_ptr<EntityManager::EntityContainer> & everyEntityContainer) override;
};

