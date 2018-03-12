#pragma once
#include "SystemsManager.h"

enum class Scope { Global, Local };

template<class ...EntityTypes>
class EntityModule // : public Module<...>
{
public:

	template<class T>
	using EPtr_t = std::unique_ptr<T>;

	template<class T>
	using EContainer_t = std::unordered_map<EntityId, EPtr_t<T>>;

	using EHolder_t = TuplePlus<EContainer_t<EntityTypes>...>;


public:

	template<class T, class ...Args_t>
	const EPtr_t<T> & spawnEntity(Args_t&&... args);

	template<class T>
	void destroyEntity(const EPtr_t<T> & entity);

	template<class T>
	void destroyEntity(EntityId id);

	// slow solution for entity destruction (it goes through every entity type given in EntityTypes parameter pack and checks for given id)
	void destroyEntity(EntityId id)
	{
		ASSERT(false, "Used slow destroyEntity solution");
		(destroyEntity<EntityTypes>(id), ...);
	}


	void update(float_t dt);

private:

	EntityId idCounter = 0;

	EHolder_t entitiesContainers;

	// add used systems here:
	SystemsManager<> systems;
};

#include "EntityModule.inl"