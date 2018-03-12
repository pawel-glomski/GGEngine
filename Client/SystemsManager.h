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
		(std::get<STypes>(systems).addEntity(entity->getId(), entity->getComponents()), ...);
	}

	void removeEntity(EntityId id)
	{
		(std::get<STypes>(systems).removeEntity(id), ...);
	}

	void update(float_t dt)
	{
		(std::get<STypes>(systems).update(dt), ...);
	}


private:

	SHolder_t systems;

};