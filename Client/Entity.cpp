#include "stdInclude.h"
#include "Entity.h"
#include "MemoryManager.h"
#include "EntityManager.h"

EntityID Entity::getID()
{
	return id;
}

void Entity::destroy()
{
	destroyed = true;
}

void Entity::attachTo(Entity * newParent)
{
	ASSERT(newParent, "Tried to attach to nullptr");
	if (newParent && this->parent != newParent)
	{
		ASSERT(!this->parent, "Attaching to entity while already being attached to one");
		unattach();
		newParent->attached.insert(this);
		parent = newParent;
	}
}

void Entity::unattach() noexcept
{
	if (parent)
		if (parent->attached.count(this))
		{
			parent->attached.erase(this);
			parent = nullptr;
		}
}

void Entity::setRelativeRotation(float_t rotation)
{
	relativeTransform.setRotation(rotation);
}

void Entity::setGlobalRotation(float_t rotation)
{
	if(parent)
		relativeTransform.setRotation(parent->getGlobalRotation() + rotation);
	else 
		relativeTransform.setRotation(rotation);
}

void Entity::rotate(float_t deltaRotation)
{
	relativeTransform.rotate(deltaRotation);
}

void Entity::setRelativePosition(const Vect2f & newPosition )
{
	relativeTransform.setPosition(newPosition);
}

void Entity::setGlobalPosition(const Vect2f & newPosition )
{
	if (parent)
		setRelativePosition(newPosition - parent->getGlobalPosition());
	else
		setRelativePosition(newPosition);
}

void Entity::moveInGlobal(const Vect2f & translationVector )
{
	relativeTransform.moveGlobal(translationVector);
}

void Entity::moveInLocal(const Vect2f & translationVector )
{
	relativeTransform.moveLocal(translationVector);
}

void Entity::moveForward(float_t distance)
{
	relativeTransform.moveForward(distance);
}

void Entity::moveRight(float_t distance)
{
	relativeTransform.moveRight(distance);
}

float_t Entity::getRelativeRotation() const
{
	return relativeTransform.getRotation();
}

float_t Entity::getGlobalRotation() const
{
	if (parent)
		return parent->getGlobalRotation() + relativeTransform.getRotation();
	return relativeTransform.getRotation();
}

Vect2f Entity::getRelativePosition() const
{
	return relativeTransform.getPosition();
}

Vect2f Entity::getGlobalPosition() const
{
	if(parent)
		return parent->getGlobalPosition() + relativeTransform.getPosition();
	return relativeTransform.getPosition();	 
}

Vect2f Entity::getForwardVector() const
{
	if (parent)
		return forwardVectorFromRotation(getGlobalRotation());
	return relativeTransform.getForwardVector();
}

Vect2f Entity::getRightVector() const
{
	if (parent)
		return rightVectorFromRotation(getGlobalRotation());
	return relativeTransform.getRightVector();
}

const Transformation & Entity::getRelativeTransform() const
{
	return relativeTransform;
}

void Entity::update(float deltaTIme)
{
}
