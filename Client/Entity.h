#pragma once
#include <memory>
#include "stdInclude.h"
#include "MathUtilities.h"
#include "TuplePlus.h"
#include "EntityBase.h"
#include "AttachableComponent.h"

class ObjectModule;

template<class ...CTypes>
class Entity : public EntityBase
{
public:

	using UsedCPack_t = CPack_t<CTypes...>;

	using UsedCRefPack_t = CRefPack_t<CTypes...>;

protected:

	// the base for inheriting types
	using EntityBase_t = Entity<CTypes...>;

public:

	Entity();

	Entity(const Entity &) = delete;

	Entity(Entity&&) = default;

	Entity& operator=(Entity &&) = default;

	Entity& operator=(const Entity &) = delete;


	virtual ~Entity()
	{
		(getComponent<CTypes>().onDestroy(), ...);
		(assertOneReference<CTypes>(), ...);
	}


	 // default implementation
	virtual void construct(ObjectModule& objectModule)
	{}




	template<class T>
	T& getComponent() const;

	template<class T>
	const CPtr_t<T>& getComponentPtr() const;

	const UsedCPack_t& getComponents() const;


	UsedCRefPack_t getComponentsRefPack() const;


protected:

	template<class T>
	void assertOneReference();


private:

	UsedCPack_t components;

};

#include "Entity.inl"