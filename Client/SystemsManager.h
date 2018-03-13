#pragma once
#include "System.h"

template<class ...STypes>
class SystemsManager
{
	using SHolder_t = TuplePlus<STypes...>;

public:

	template<class T>
	void addEntity(const T & entity)
	{
		(systems.get<STypes>().addEntity(entity.getId(), entity.getComponents()), ...);
	}

	void removeEntity(EntityId id)
	{
		(systems.get<STypes>().removeEntity(id), ...);
	}

	void update(float_t dt)
	{
		(systems.get<STypes>().update(dt), ...);
	}


private:

	SHolder_t systems;

};