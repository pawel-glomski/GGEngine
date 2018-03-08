#include "EntityUpdateSystem.h"

void EntityUpdateSystem::addEntity(const EntityManager::EntityPtr & entity, const std::shared_ptr<EntityManager::EntityContainer> & everyEntityContainer)
{
	if (!entitiesToUpdate)
	{
		if (usesEveryEntity)
			entitiesToUpdate = everyEntityContainer;
		else
			entitiesToUpdate = std::make_shared<std::unordered_map<Entity::ID, EntityManager::EntityPtr>>();
	}

	ASSERT(entity, "Tried to add nullptr entity");
	if (entity)
		(*entitiesToUpdate)[entity->getID()] = entity;
}

void EntityUpdateSystem::removeEntity(const Entity::ID & entity)
{
	if (!usesEveryEntity)
		if (entitiesToUpdate && entitiesToUpdate->count(entity))
			entitiesToUpdate->erase(entity);
}

void EntityUpdateSystem::reset()
{
	entitiesToUpdate.reset();
}