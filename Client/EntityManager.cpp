#include "EntityManager.h"
#include "EntityUpdateSystem.h"

EntityManager::EntityPtr EntityManager::unidentifiedEntityPtr; 

void EntityManager::startUp()
{
	entities = std::shared_ptr<EntityContainer>(MemoryManager::stack.allocObject<EntityContainer>(), MemoryManager::StackDeleter<EntityContainer>());
}

void EntityManager::shoutDown()
{
	for (auto & system : systems)
		system->reset();
	systems.clear();

	for (auto & entity : *entities)
		entity.second->removeAllComponents();
	entities.reset();
}

void EntityManager::update(float_t dt)
{
	addSpawnedEntities();
	deleteDeadEntities();

	for (auto & system : systems)
		system->update(*this, dt);
}

void EntityManager::addSpawnedEntities()
{
	for (auto & system : systems)
		for (auto & entity : spawnedEntities)
			system->addEntity(entity, entities);
	spawnedEntities.clear();
}

void EntityManager::deleteDeadEntities()
{
	for (auto & entity : deadEntities)
	{
		entities->erase(entity->getID());
		for (auto & system : systems)
			system->removeEntity(entity->getID());

		entity->removeAllComponents(); // removes all components => releases relations
		ASSERT(entity.unique(), "Deleting entity that is referenced outside of EntityManager! That reference is uselss now, this entity will no longer be updated");
	}
	deadEntities.clear();
}

void EntityManager::addSystem(const std::shared_ptr<EntityUpdateSystem>& system)
{
	ASSERT(system, "Tried to add nullptr system!");
	ASSERT(!entities->size(), "Added system, when there are already spawned entities! System was added after client's startup, or entity was spawned before startup");
	if (system)
	{
		std::type_index typeIndex(typeid(*system));

		for(auto & system : systems)
			if (std::type_index(typeid(*system)) == typeIndex)
			{
				ASSERT(false, std::string("Tried to add multiple systems of the same type (only one system of a type can be managed by EntityManager) ") + typeIndex.name());
				return;
			}
		systems.push_back(system);
	}
}

const EntityManager::EntityPtr & EntityManager::getEntity(Entity::ID id)
{
	if (entities->count(id))
		return (*entities)[id];

	ASSERT(false, "Tried to get entity with unidentified id");
	return unidentifiedEntityPtr;
}

void EntityManager::destroyTempEntity(Entity::ID id)
{
	ASSERT(entities->count(id), "Tried to destroy entity with unidentified temp id");
	if (entities->count(id))
	{
		auto & entity = (*entities)[id];
		ASSERT(entity->getComponent<LifetimeComponent>()->isDying(), "Tried to destroy alive entity (this means that destroyTempEntity was not called by LifetimeSystem)");
		if (entity && entity->getComponent<LifetimeComponent>()->isDying())
			deadEntities.push_back(entity);
	}
}