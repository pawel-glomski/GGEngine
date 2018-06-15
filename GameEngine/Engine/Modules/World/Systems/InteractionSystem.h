#pragma once
#include <ECSpp/System.h>
#include <random>
#include "Modules/Controller/ControllerModule.h"

#include "Modules/World/Components/CollisionComponent.h"
#include "Modules/World/Components/TransformComponent.h"
#include "Modules/World/Components/PhysicsComponent.h"
#include "Modules/World/Components/ShapeComponent.h"


class InteractionSystem : public epp::System
{
public:

	InteractionSystem(const ControllerModule & controllerModule);


	virtual void init(epp::EntityManager& entityManager) override;

	virtual void update(epp::EntityManager& entityManager, float dt) override;


	bool shouldDrawCollisions() const;

	bool shouldDrawCollisionGrid() const;

private:

	void drag();

	void spawn(epp::EntityManager & entityManager);

	void displayControll();

private:

	epp::CGroup<CollisionComponent, ShapeComponent, PhysicsComponent, TransformComponent> entities;

	epp::EntityRef draggedEntity;

	c2Circle cursor;


	bool isDrawingCollisions = true;

	bool isDrawingCollisionGrid = true;


	std::random_device rd;

	std::uniform_real_distribution<float> dist = std::uniform_real_distribution<float>(0.f, 4.f);

	const ControllerModule & controllerModule;
};