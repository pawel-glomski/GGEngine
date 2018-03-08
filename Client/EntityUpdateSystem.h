#pragma once
#include <corecrt_math.h>
#include <memory>
#include "Entity.h"
#include "EntityManager.h"

class EntityUpdateSystem
{
public:
	
	EntityUpdateSystem() = default;

	virtual ~EntityUpdateSystem() = default;


	virtual void update(EntityManager & entityManager, float_t dt) = 0;


	// adds entity to list of entities, that system will update (if entity owns appropriate components)
	// on first call, system may allocate its own entity container, or use everyEntityContainer one, if it will update every entity
	// base implementation always creates its own container and adds given entity to it if its not nullptr
	// if system will update every entity (like LifetimeSystem), usesEveryEntity member must be set to true!
	virtual void addEntity(const EntityManager::EntityPtr & entity, const std::shared_ptr<EntityManager::EntityContainer> & everyEntityContainer);

	// 1) usesEveryEntity == true ---> function does nothing (entity is deleted in entityManager)
	// 2) usesEveryEntity == false --> function removes entity from entitiesToUpdate
	virtual void removeEntity(const Entity::ID & entity);

	// resets entitiesToUpdate
	virtual void reset();

protected:

	bool usesEveryEntity = false;

	std::shared_ptr<std::unordered_map<Entity::ID, EntityManager::EntityPtr>> entitiesToUpdate;
};