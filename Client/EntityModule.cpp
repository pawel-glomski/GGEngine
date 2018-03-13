#include "EntityModule.h"

void EntityModule::destroyEntity(EntityId id)
{
	ASSERT(entities.count(id), "Tried to destroy entity with unidentified id!");
	systems.removeEntity(id);
	entities.erase(id);
}

void EntityModule::update(float_t dt)
{
	systems.update(dt);
}
