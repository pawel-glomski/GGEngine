#pragma once
#include "Entity.h"
#include "CollisionShape.h"

class CollidableEntity : public Entity
{
public:
	virtual void collideWith(CollidableEntity & entity);

private:
	
	CollisionShape collisionShape;
};

