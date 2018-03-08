#pragma once
#include <unordered_set>
#include "Character.h"
#include "Projectile.h"
#include "AudioEffect.h"
#include "VisualEffect.h"
#include "MemoryManager.h"


class EntityManager
{
public:
	virtual void startUp();
	virtual void shoutDown();

	void updateEntities(float_t deltaTime);

	void display(sf::RenderWindow & window) const;

	// pass id, to create entity with given id, pass nothing to use any free id
	// returns nullptr if there already exists entity with given id
	template<class T>
	T* spawnTempEntity(EntityID id = -1);

	void destroyTempEntity(const EntityID & id);

	// pass id, to create entity with given id, pass nothing to use any free id
	// returns nullptr if there already exists entity with given id
	// cannot destroy/free those in runtime
	template<class T>
	T* spawnPermEntity(EntityID id = -1);

private:
	// use as unordered_map::erase member function
	std::unordered_map<EntityID, Entity*>::iterator destroyTempByIterator(const std::unordered_map<EntityID, Entity*>::iterator it);

private:
	std::unordered_map<EntityID, Entity*> permEntities;
	std::unordered_map<EntityID, Entity*> tempEntities;
};

template<class T>
inline T * EntityManager::spawnTempEntity(EntityID id)
{
	ASSERT(!tempEntities.count(id), "Tried to spawn entity with id of other spawned entity! Spawned nothing, returned nulltpr");
	if (tempEntities.count(id))
		return nullptr;

	auto ptr = MemoryManager::instance().allocFromPool<T>();
	ASSERT(ptr, "Cannot spawn entity, no memory was allocated for it, returned nullptr");
	if (ptr)
	{
		tempEntities[id] = ptr;
		ptr->id = id;
	}
	return ptr;
}

template<class T>
inline T * EntityManager::spawnPermEntity(EntityID id)
{
	ASSERT(!permEntities.count(id), "Tried to spawn entity with id of already spawned entity! Spawned nothing, returned nulltpr");
	if (permEntities.count(id))
		return nullptr;

	auto ptr = MemoryManager::instance().stack.allocConstructed<T>();
	ASSERT(ptr, "Cannot spawn entity, no memory was allocated for it, returned nullptr");
	if (ptr)
	{
		permEntities[id] = ptr;
		ptr->id = id;
	}
	return ptr;
}
