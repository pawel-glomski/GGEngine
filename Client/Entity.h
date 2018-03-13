#pragma once
#include <memory>
#include "MathUtilities.h"
#include "TuplePlus.h"

using EntityId = uint32_t;

struct EntityBase
{
	EntityBase(EntityId id) : id(id) {}

	virtual ~EntityBase() = default;


	EntityId getId() const
	{
		return id;
	}


protected:

	static const uint32_t unidentifiedID = 0;

	EntityId id = unidentifiedID;

};

template<class ...Types>
class Entity : public EntityBase
{
public:

	// base for inherting types
	using Base_t = Entity<Types...>;

	template<class T>
	using CPtr_t = std::shared_ptr<T>;

	using CHolder_t = TuplePlus<CPtr_t<Types>...>;

public:

	Entity(EntityId id);

	Entity(const Entity &) = delete;

	Entity(Entity&&) = delete;

	Entity& operator=(const Entity &) = delete;

	Entity& operator=(Entity &&) = delete;

	virtual ~Entity() = default;


	// overrided by inherted types (if needed)
	template<class U>
	void construct(U & entityModule) {}



	template<class T>
	CPtr_t<T>& getComponent();


	template<class T>
	const CPtr_t<T> & getComponent() const;


	CHolder_t & getComponents();


	const CHolder_t & getComponents() const;


private:

	CHolder_t components;

};

#include "Entity.inl"