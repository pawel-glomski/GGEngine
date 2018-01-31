#include "stdInclude.h"
#include "Entity.h"
#include "MemoryManager.h"
#include "EntityManager.h"

Entity::Entity()
{
	attached.reserve(6);
}

Entity::~Entity()
{
}

void Entity::setName(std::string newName)
{
	ASSERT(!newName.empty(), "Name was set to empty string");
	name = std::move(newName);
}

void Entity::selfDestroy()
{
	selfDestroyed = true;
}

void Entity::onDestroy()
{
	parent = nullptr;
	attached.clear();
}

void Entity::constructComplexEntity(EntityManager & entityManager)
{
}

void Entity::attachTo(Entity * newParent)
{
	ASSERT(newParent, "Tried to attach to nullptr");
	if (newParent && this->parent != newParent)
	{
		ASSERT(!this->parent, "Attaching to entity while already being attached to one");
		unattach();
		newParent->attached.insert(this);
	}
}

void Entity::unattach()
{
	if (parent)
		if (parent->attached.count(this))
		{
			parent->attached.erase(this);
			parent = nullptr;
		}
}

void Entity::setRelativePosition(const Vect2f & newPosition, bool sweep)
{
	if (sweep)
	{	
		//sweep process ...
	}

	relativePosition = newPosition;
	updateGlobalPosition();
}

void Entity::setGlobalPosition(const Vect2f & newPosition, bool sweep)
{
	if (sweep)
	{
		//sweep process ...
	}

	globalPosition = newPosition;
	updateRelativelPosition();
}

void Entity::updateRelativelPosition()
{
	if (parent)
		relativePosition = globalPosition - parent->getGlobalPosition();
	else
		relativePosition = globalPosition;

	for (auto& child : attached)
		child->updateGlobalPosition();
}

void Entity::updateGlobalPosition()
{
	if (parent)
		globalPosition = parent->getGlobalPosition() + relativePosition;
	else
		globalPosition = relativePosition;

	for (auto& child : attached)
		child->updateGlobalPosition();
}

void Entity::moveInGlobal(const Vect2f & translationVector, bool sweep)
{
	setGlobalPosition(globalPosition + translationVector);
}

void Entity::moveInLocal(const Vect2f & translationVector, bool sweep)
{
	// rotation based move
	ASSERT(false, "MoveInLocal is not implemented yet");
}

std::string Entity::getName()
{
	ASSERT(!name.empty(), "Returned empty string");
	return name;
}

Vect2f Entity::getRelativePosition() const
{
	return relativePosition;
}

Vect2f Entity::getGlobalPosition() const
{
	return globalPosition;
}

void Entity::update(float deltaTIme)
{
	// update itself

}
