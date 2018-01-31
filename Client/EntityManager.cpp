#include "EntityManager.h"
#include "MemoryManager.h"

void EntityManager::startUp()
{
	permEntities.reserve(1000);
	tempEntities.reserve(1000);
	destroyPendingTempEntities.reserve(100);
}

void EntityManager::shoutDown()
{
	// deallocate in opposite order to allocation
	for(int32_t i = permEntities.size() - 1; i >= 0; i--)
		MemoryManager::instance().stack.freeToConstructed(permEntities[i]);
	permEntities.reserve(0);
	tempEntities.reserve(0);
	destroyPendingTempEntities.reserve(0);
}

void EntityManager::updateEntities(float_t deltaTime)
{
	for (auto & entity : permEntities)
		entity->update(deltaTime);

	for (auto & entity : tempEntities)
		if (entity->selfDestroyed)
			destroyPendingTempEntities.push_back(entity);
		else
			entity->update(deltaTime);

	// destroy self-destroyed entities
	for (auto & entity : destroyPendingTempEntities)
		destroyTempEntity(entity);
}

void EntityManager::display(sf::RenderWindow & window) const
{
	for (auto & entity : permEntities)
		entity->display(window);
	for (auto & entity : tempEntities)
		entity->display(window);
}

void EntityManager::destroyTempEntity(Entity * ptr)
{
	ASSERT(ptr, "Tried to destroy nullptr entity");
	if (!ptr)
		return;

	ASSERT(tempEntities.count(ptr), "Tried to destroy entity that was not created in EntityManager or was already destroyed");
	if (tempEntities.count(ptr))
	{
		if (ptr->parent)
			ptr->parent->attached.erase(ptr);
		for (auto& child : ptr->attached)
			destroyTempEntity(child);

		ptr->onDestroy();
		tempEntities.erase(ptr);
		MemoryManager::instance().freeToPool(ptr);
		ptr = nullptr;
	}
}