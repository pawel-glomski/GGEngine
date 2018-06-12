#pragma once
#include "Entity.h"
#include "ControllerComponent.h"
#include "AbilityComponent.h"
#include "DisplayComponent.h"
#include "TransformComponent.h"
#include "RelationComponent.h"
#include "LifetimeComponent.h"

class Character : public Entity
{
public:

	virtual void construct(class EntityManager & entityManager) override;
};