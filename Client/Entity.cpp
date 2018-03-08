#include "Entity.h"
#include "stdInclude.h"
#include "MemoryManager.h"
#include "LifetimeComponent.h"
#include "TransformComponent.h"
#include "RelationComponent.h"
#include "EntityManager.h"

Entity::~Entity()
{
	ASSERT(components.empty(), 
		"Entity is being destroyed before removing all of its components! This must be done by entity manager before entity is destroyed! Entity is removing components by itself now");
	removeAllComponents();
}

void Entity::construct(EntityManager & entityManager)
{
	addComponent<LifetimeComponent>();
	addComponent<RelationComponent>()->setOwningEntity(entityManager.getEntity(getID()));
	addComponent<TransformComponent>();
}

void Entity::setID(ID id)
{
	ASSERT(this->id == unidentifiedID, "Set new id to an entity that already had one");
	this->id = id;

}

bool Entity::isConstructed() const
{
	return components.size();
}

Entity::ID Entity::getID() const
{
	return id;
}

void Entity::removeAllComponents()
{
	// remove relation component first, so other components (like transform) are still valid
	components.erase(std::type_index(typeid(RelationComponent)));
	components.clear();
}