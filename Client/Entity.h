#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include "stdInclude.h"
#include "MemoryManager.h"
#include "Component.h"

// entities can be ONLY spawned by EntityManager
class Entity
{
public:

	enum class Scope { Global, Local };

	
	//ID that identifies entity in the EntityManager. There are 2 types of ids:
	//1) Global IDs, that are for entities that are both on server's and client's sides. Range: <1 ; UINT32_MAX / 2)
	//2) Local ones, that are only for client entites (audio effects, visual effects, etc). Range: <UINT32_MAX / 2 ; UINT32_MAX)
	//0 - unidentified id
	using ID = uint32_t;

	static const uint32_t unidentifiedID = 0;

public:

	Entity() = default;

	Entity(const Entity &) = delete;

	virtual ~Entity();

	// constructs components, that will be used by systems
	// Entity::construct (base implementation) - adds essential components
	virtual void construct(class EntityManager & entityManager);

	bool isConstructed() const;


	// pointers returned shouldn't be saved anywhere; Temp entities may be destroyed in runtime, so references to this component may be invalidated
	template<class T>
	T* getComponent() const;

	void removeAllComponents();


	void setID(ID id);

	ID getID() const;

protected:
	template<class T>
	T* addComponent();

private:
	
	std::unordered_map<std::type_index, std::unique_ptr<Component>> components;

	ID id = unidentifiedID;	// id is given only by entity manager!
};

template<class T>
inline T* Entity::getComponent() const
{
	std::type_index typeIndex = std::type_index(typeid(T));
	if (components.count(typeIndex))
		return static_cast<T*>(components.at(typeIndex).get());
	return nullptr;
}

template<class T>
inline T* Entity::addComponent()
{
	std::type_index compType = std::type_index(typeid(T));
	ASSERT(!components.count(compType), std::string("Tried to add component of a type, that entity already has. Type: ") + compType.name() + ". Returned nullptr");
	if (!components.count(compType))
	{
		components[compType] = std::make_unique<T>();
		return static_cast<T*>(components[compType].get());
	}
	return nullptr;
}