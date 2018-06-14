#pragma once
#include <ECSpp/System.h>
#include <random>
#include "ControllerModule.h"

#include "CollisionComponent.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "ShapeComponent.h"


class InteractionSystem : public epp::System
{
public:

	InteractionSystem(const ControllerModule & controllerModule);


	virtual void init(epp::EntityManager& entityManager) override;

	virtual void update(epp::EntityManager& entityManager, float dt) override;

private:

	void drag();

	void spawn(epp::EntityManager & entityManager);

private:

	epp::CGroup<CollisionComponent, ShapeComponent, PhysicsComponent, TransformComponent> entities;

	epp::EntityRef draggedEntity;

	c2Circle cursor;

	std::random_device rd;

	std::uniform_real_distribution<float> dist = std::uniform_real_distribution<float>(0.f, 4.f);


	size_t spawnedCount = 0;

	const ControllerModule & controllerModule;
};