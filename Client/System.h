#pragma once
#include <unordered_map>
#include "stdInclude.h"
#include "Entity.h"
	


template<class ...CTypes>
class System
{
	static_assert(sizeof...(CTypes), "Cannot create System with empty parameter pack");

public:

	template<class T>
	using CPtr_t = std::shared_ptr<T>;

	using CHolder_t = TuplePlus<CPtr_t<CTypes>...>;

	using CContainer_t = std::unordered_map<EntityId, CHolder_t>;

public:


	template<class ...Dependencies>
	void init(const TuplePlus<Dependencies...> & dep);

	virtual void update(float_t dt) = 0;



	// does nothing
	template<class ...EntityCTypes>
	typename std::enable_if< !TuplePlus<EntityCTypes...>::template AreUsed<CTypes...>::value, void>::type
		addEntity(EntityId, const TuplePlus<CPtr_t<EntityCTypes>...> &) {} 

	// adds components of entity
	template<class ...EntityCTypes>
	typename std::enable_if< TuplePlus<EntityCTypes...>::template AreUsed<CTypes...>::value, void>::type
		addEntity(EntityId id, const TuplePlus<CPtr_t<EntityCTypes>...> & componentsHolder);


	void removeEntity(EntityId id);


protected:

	CContainer_t entitiesComponents;

};

#include "System.inl"