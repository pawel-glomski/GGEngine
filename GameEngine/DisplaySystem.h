#pragma once
#include <ECSpp/System.h>
#include "DisplayModule.h"

#include "TransformComponent.h"
#include "ShapeComponent.h"
#include "DisplayComponent.h"
#include "CollisionComponent.h"

#include "CollisionSystem.h"

class DisplaySystem : public epp::System
{
public:

	DisplaySystem(DisplayModule& displayModule, const CollisionSystem& colSys);

	virtual void init(epp::EntityManager& entityManager) override;

	virtual void update(epp::EntityManager& entityManager, float dt) override;

private:

	void drawEntities();

	void drawCollisions();

	void drawCollisionGrid();

private:

	epp::CGroup<DisplayComponent, TransformComponent, ShapeComponent> entities;

	epp::CGroup<DisplayComponent, TransformComponent, ShapeComponent, CollisionComponent> entitiesWithCollisions;

	DisplayModule& displayModule;

	const CollisionSystem& colSys;
};