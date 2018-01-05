#include "stdInclude.h"
#include "Entity.h"

void Entity::setPosition(const Vect2f & newPosition, bool sweep)
{
	if (!sweep)
	{
		position = newPosition;
	}
}

void Entity::move(const Vect2f & translationVector, bool sweep)
{
	if (!sweep)
	{
		position += translationVector;
	}
}
