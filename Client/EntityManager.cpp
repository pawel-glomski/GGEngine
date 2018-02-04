#include "EntityManager.h"
#include "MemoryManager.h"

void EntityManager::startUp()
{
	permEntities.reserve(1000);
	tempEntities.reserve(1000);
}

void EntityManager::shoutDown()
{
	// destroy stack-constructed perm objects
	for (auto & entity : permEntities)
		MemoryManager::instance().stack.freeToConstructed(entity.second);
	permEntities.reserve(0);
	tempEntities.reserve(0);
}

void EntityManager::updateEntities(float_t deltaTime)
{
	for (auto & entity : permEntities)
		entity.second->update(deltaTime);

	for (auto it = tempEntities.begin(); it != tempEntities.end();)
		if (it->second->destroyed)	// The order of the elements that are not erased is preserved (this makes it possible to erase individual elements while iterating through the container)
			it = destroyTempByIterator(it);
		else
		{
			it->second->update(deltaTime);
			it++;
		}
}

void EntityManager::display(sf::RenderWindow & window) const
{
	for (auto & entity : permEntities)
		entity.second->display(window);
	for (auto & entity : tempEntities)
		entity.second->display(window);
}

void EntityManager::destroyTempEntity(const EntityID & id)
{
	ASSERT(tempEntities.count(id), "Tried to destroy entity that was not created in EntityManager or is already destroyed");
	if (tempEntities.count(id))
		destroyTempByIterator(tempEntities.find(id));
}

std::unordered_map<EntityID, Entity*>::iterator EntityManager::destroyTempByIterator(const std::unordered_map<EntityID, Entity*>::iterator it)
{
	Entity * ptr = it->second;
	if (ptr->parent)
	{
		ptr->parent->attached.erase(ptr);
		ptr->parent = nullptr;
	}
	for (auto& child : ptr->attached)
		destroyTempEntity(child->id);
	ptr->attached.clear();
	MemoryManager::instance().freeToPool(ptr);
	return tempEntities.erase(it);
}