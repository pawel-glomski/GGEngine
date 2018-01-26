#include "EntityManager.h"
#include "MemoryManager.h"

void EntityManager::startUp()
{
	permEntities.reserve(1000);
	tempEntities.reserve(1000);
}

void EntityManager::shoutDown()
{
	permEntities.resize(0);
	tempEntities.clear();
}

void EntityManager::updateEntities(float_t deltaTime)
{
	for (auto & entity : permEntities)
		entity->update(deltaTime);
	for (auto & entity : tempEntities)
		entity->update(deltaTime);
}

void EntityManager::display(sf::RenderWindow & window) const
{
	for (auto & entity : permEntities)
		entity->display(window);
	for (auto & entity : tempEntities)
		entity->display(window);
}

void EntityManager::destroyTempEntity(Entity *& ptr)
{
	ASSERT(ptr, "Tried to destroy nullptr entity");
	if (!ptr)
		return;
	;

	ASSERT(tempEntities.count(ptr), "Tried to destroy entity that was not created in EntityManager is or already destroyed");
	if (tempEntities.count(ptr))
	{
		for (auto& child : ptr->attached)
			destroyTempEntity(child);

		ptr->onDestroy();
		tempEntities.erase(ptr);
		MemoryManager::instance().freeToPool(ptr);
		ptr = nullptr;
	}
}