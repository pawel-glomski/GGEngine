#pragma once
#include "Entity.h"
class Obstacle :
	public Entity
{
public:
	virtual void construct(class EntityManager & entityManager) override;
};

