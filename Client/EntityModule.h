#pragma once
#include "Module.h"
#include "DisplayModule.h"
#include "SystemsManager.h"

enum class Scope { Global, Local };

class EntityModule : public Module<DisplayModule>
{
	template<class T>
	using EPtr_t = std::unique_ptr<T>;

	using EContainer_t = std::unordered_map<EntityId, EPtr_t<EntityBase>>;


public:

	template<class ...MPtrTypes>
	EntityModule(TuplePlus<MPtrTypes...> & modules) : Base_t(modules) {};


	template<class T, class ...Args_t>
	T& spawnEntity(Args_t&&... args);

	void destroyEntity(EntityId id);


	void update(float_t dt);

private:

	EntityId idCounter = 0;

	EContainer_t entities;

	// add used systems here:
	SystemsManager<> systems;
};

template<class T, class ...Args_t>
inline T& EntityModule::spawnEntity(Args_t && ...args)
{
	EPtr_t<T> entity = std::make_unique<T>(++idCounter, std::forward<Args_t>(args)...);
	T& entityRef = *entity;
	entities[entityRef.getId()] = std::move(entity);

	systems.addEntity(entityRef);
	entityRef.construct(*this);

	return entityRef;
}