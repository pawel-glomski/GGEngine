#pragma once
#include <memory>
#include <unordered_set>
#include "MemoryManager.h"
#include "Character.h"

class EntityUpdateSystem;

class EntityManager
{
	friend class LifetimeSystem;
public:

	using EntityDeleter = MemoryManager::PoolDeleter<Entity> ;

	using EntityPtr = std::shared_ptr<Entity>;

	using EntityContainer = std::unordered_map<Entity::ID, EntityPtr>;

	using PendingEntityContainer = std::vector<EntityPtr>;


	static EntityPtr unidentifiedEntityPtr;	// just an empty ptr, that reference to it is returned when we cant get wanted object


public:

	void startUp();

	void shoutDown();


	// runs added systems to update entities
	void update(float_t dt);

	
	// order in which systems will be added will be order in which systems will update entities
	void addSystem(const std::shared_ptr<EntityUpdateSystem> & system);


	// spawned entity will be added to update loop with next update call
	// returned pointer shouldn't be saved as shared, so when entity is destroyed, only entity manager owns a pointer to that entity
	template<class T, class ... Args>
	const EntityPtr & spawnEntity(Entity::Scope scope, Lifetime lifetime, Args&&...args);

	// returned pointer shouldn't be saved as shared, so when entity is destroyed, only entity manager owns a pointer to that entity
	const EntityPtr & getEntity(Entity::ID id);

private:

	void addSpawnedEntities();

	void deleteDeadEntities();

	void destroyTempEntity(Entity::ID id);

	template<class T, class ... Args>
	const EntityPtr & allocEntity(Lifetime lifetime, Entity::ID id, Args&&... args);

private:

	Entity::ID globalEntityIDCounter = Entity::unidentifiedID + 1; // 0 is unidentified id

	Entity::ID localEntityIDCounter = std::numeric_limits<Entity::ID>::max() / 2;


	std::shared_ptr<EntityContainer> entities;

	PendingEntityContainer spawnedEntities;

	PendingEntityContainer deadEntities;


	std::vector<std::shared_ptr<EntityUpdateSystem>> systems;

};




template<class T, class ...Args>
inline const EntityManager::EntityPtr & EntityManager::spawnEntity(Entity::Scope scope, Lifetime lifetime, Args&&... args)
{
	if (scope == Entity::Scope::Global)
	{
		if (globalEntityIDCounter + 1 < std::numeric_limits<Entity::ID>::max() / 2)
			return allocEntity<T>(lifetime, globalEntityIDCounter++, std::forward<Args>(args)...);
	} 
	else if (localEntityIDCounter + 1 < std::numeric_limits<Entity::ID>::max())
		return allocEntity<T>(lifetime, localEntityIDCounter++, std::forward<Args>(args)...);

	ASSERT(false, "Out of entity ids, returns reference to empty ptr");
	return unidentifiedEntityPtr;
}

template<class T, class ...Args>
inline const EntityManager::EntityPtr & EntityManager::allocEntity(Lifetime lifetime, Entity::ID id, Args&&... args)
{
	EntityPtr newEntity = EntityPtr(MemoryManager::allocFromPool<T>(std::forward<Args>(args)...), EntityDeleter());
	if (newEntity)
	{		
		spawnedEntities.push_back(newEntity);
		(*entities)[id] = newEntity;
		newEntity->setID(id);
		// to get component, first construct entity
		newEntity->construct(*this);
		newEntity->getComponent<LifetimeComponent>()->setLifetime(lifetime);

		return (*entities)[id];
	}
	ASSERT(false, "No memory was allocated for entity, returns reference to empty ptr");
	return unidentifiedEntityPtr;
}
