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

	template<class T>
	T* spawnTempEntity();

	void destroyTempEntity(Entity * ptr);

	// cannot destroy/free those
	template<class T>
	T* spawnPermEntity();

private:
	std::vector<Entity*>		permEntities;
	std::unordered_set<Entity*> tempEntities;
	std::vector<Entity*>		destroyPendingTempEntities;
};

template<class T>
inline T * EntityManager::spawnTempEntity()
{
	auto ptr = MemoryManager::instance().allocFromPool<T>();
	ASSERT(ptr, "Cannot spawn entity, no memory was allocated for it, returned nullptr");
	if (ptr)
	{
		tempEntities.insert(ptr);
		ptr->constructComplexEntity(*this);
		ptr->onSpawn();
	}
	return ptr;
}

template<class T>
inline T * EntityManager::spawnPermEntity()
{
	auto ptr = MemoryManager::instance().stack.allocConstructed<T>();
	ASSERT(ptr, "Cannot spawn entity, no memory was allocated for it, returned nullptr");
	if (ptr)
	{
		permEntities.push_back(ptr);
		ptr->constructComplexEntity(*this);
		ptr->onSpawn();
	}
	return ptr;
}
