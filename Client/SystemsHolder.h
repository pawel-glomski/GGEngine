#pragma once
#include "System.h"

template<class ...STypes>
class SystemsHolder
{
public:

	using SPack_t = TypesPack_t<STypes...>;

	template<class T>
	using SystemMDepPack_t = typename T::UsedMDepPack_t;

public:

	template<class T>
	void addObject(const T & object)
	{
		(systems.get<STypes>().addObject(object), ...);
	}

	void addPendingObjects()
	{
		(systems.get<STypes>().addPendingObjects(), ...);
	}
	
	void removeObject(const CPackKey_t objKey)
	{
		(systems.get<STypes>().removeObject(objKey), ...);
	}


	template<class MDepPackType>
	void update(float_t dt, const MDepPackType& dep, ObjectModule & entityModule)
	{
		(systems.get<STypes>().update(dt, SystemMDepPack_t<STypes>::makeFromTuple(dep), entityModule), ...);
	}


private:

	SPack_t systems;
};