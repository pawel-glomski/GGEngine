#pragma once
#include <ECSpp/System.h>
#include "Modules/World/Components/PhysicsComponent.h"
#include "Modules/World/Components/CollisionComponent.h"
#include "Modules/World/Components/TransformComponent.h"


class PhysicsSystem : public epp::System
{
	using EntitesGroup_t = epp::CGroup<PhysicsComponent, CollisionComponent, TransformComponent>;

	using GroupIterator_t = EntitesGroup_t::Iterator_t;

public:

	virtual void init(epp::EntityManager& entityManager) override;

	virtual void update(epp::EntityManager& entityManager, float dt) override;

private:

	void fixSinking();

	void resolveCollisions();

	void applyGravity(float dt);

	void resolveVelocities(float dt);

private:

	EntitesGroup_t entities;
};

