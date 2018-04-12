#pragma once
#include <unordered_map>
#include "IdentityComponent.h"
#include "Module.h"
#include "TypesPacksContainer.h"

class ObjectModule;


using CPackKey_t = CPtr_t<IdentityComponent>;

template<class CPackType>
using CPacksContainer_t = TypesPacksContainer<CPackKey_t, CPackType>;

// MDepPackType = Module<DTypes...>
// CRefPackType = CRefPack_t<CTypes...>
template<class MDepPackType, class CRefPackType, bool defaultImplementation = true>
class System 
{
	static_assert(!std::is_same_v<CRefPackType, CRefPack_t<>>, "Cannot create System with an empty parameter pack");

public:

	using UsedMDepPack_t = MDepPackType;

protected:

	using SystemBase_t = System<MDepPackType, CRefPackType>;


	using UsedCRefPack_t = CRefPackType;

	using UsedCPacksContainer_t = CPacksContainer_t<UsedCRefPack_t>;

	using UsedCPacksContainerPtr_t = StdUPtr_t<UsedCPacksContainer_t>;


public:

	System()
	{
		if(defaultImplementation)
			objectsCPacks = std::make_unique<UsedCPacksContainer_t>();
	}

	template<class T>
	void addObject(const T& object)
	{
		static_assert(defaultImplementation, "Cannot use system's default functions while defaultImplementation is set to false");
		objectsCPacks->addPack(object.getComponentPtr<IdentityComponent>(), object.getComponentsRefPack());
	}

	void removeObject(const CPackKey_t & objKey)
	{
		static_assert(defaultImplementation, "Cannot use system's default functions while defaultImplementation is set to false");
		objectsCPacks->removePack(objKey);
	}

	virtual void addPendingObjects()
	{
		static_assert(defaultImplementation, "Cannot use system's default functions while defaultImplementation is set to false");
		objectsCPacks->addPendingPacks();
	}

	virtual void update(float_t dt, const UsedMDepPack_t& dependencies, ObjectModule & objectModule) = 0;

protected:

	UsedCPacksContainerPtr_t objectsCPacks;
};

