#pragma once
#include <chrono>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include "stdInclude.h"
#include "DisplayManager.h"
#include "RawInputReceiver.h"
#include "EntityUpdateSystem.h"
#include "EntityManager.h"
#include "PlayerController.h"

class Client
{
public:

	void play();

private:

	virtual void startUp();

	void systemsStartUp();

	virtual void shoutDown();

	void systemsShoutDown();


private:

	float calcDeltaTime(std::chrono::high_resolution_clock::time_point & now, std::chrono::high_resolution_clock::time_point& last);

	template<class T> 
	std::shared_ptr<T> makeSystem();

	template<class T>
	std::shared_ptr<T> getSystem();

private:

	RawInputReceiver rawInputReceiver;

	PlayerController playerController;


	EntityManager entityManager;

	std::unordered_map<std::type_index, std::shared_ptr<EntityUpdateSystem>> entityUpdateSystems;


	std::shared_ptr<DisplayManager> displayManager;

};


template<class T>
inline std::shared_ptr<T> Client::makeSystem()
{
	std::type_index typeIndex = std::type_index(typeid(T));
	ASSERT(!entityUpdateSystems.count(typeIndex), "Tried to make system of a type that already exists!");
	std::shared_ptr<T> sptr;
	if (!entityUpdateSystems.count(typeIndex))
	{
		sptr = std::shared_ptr<T>(MemoryManager::stack.allocObject<T>(), MemoryManager::StackDeleter<T>());
		entityUpdateSystems[typeIndex] = sptr;
	}
	return sptr;
}

template<class T>
inline std::shared_ptr<T> Client::getSystem()
{
	std::type_index typeIndex = std::type_index(typeid(T));
	ASSERT(entityUpdateSystems.count(typeIndex), "Tried to get system of a type that does not exists!, returned empty pointer");
	if (entityUpdateSystems.count(typeIndex))
		return std::static_pointer_cast<T>(entityUpdateSystems[typeIndex]);

	return std::shared_ptr<T>();
}
