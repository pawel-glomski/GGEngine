#pragma once
#include <ECSpp/System.h>
#include "PhysicsComponent.h"

class PhysicsSystem : public epp::System
{
	virtual void init(epp::EntityManager& entityManager) override;

	virtual void update(epp::EntityManager& entityManager, float dt) override;
};

