#pragma once
#include <ECSpp/System.h>
#include "Modules/Display/DisplayModule.h"

#include "Modules/World/Components/TransformComponent.h"
#include "Modules/World/Components/ShapeComponent.h"
#include "Modules/World/Components/DisplayComponent.h"
#include "Modules/World/Components/CollisionComponent.h"

#include "Modules/World/Systems/CollisionSystem/CollisionSystem.h"
#include "InteractionSystem.h"


class DisplaySystem : public epp::System
{
public:

	DisplaySystem(DisplayModule& displayModule, const CollisionSystem& colSys, const InteractionSystem& intSys);

	virtual void init(epp::EntityManager& entityManager) override;

	virtual void update(epp::EntityManager& entityManager, float dt) override;

private:

	void drawEntities();

	void drawCollisions();

	void drawCollisionGrid();

private:

	epp::CGroup<DisplayComponent, TransformComponent, ShapeComponent> entities;

	epp::CGroup<DisplayComponent, TransformComponent, ShapeComponent, CollisionComponent> entitiesWithCollisions;

	bool isDrawingCollisions = false;

	bool isDrawingCollisionGrid = false;


	DisplayModule& displayModule;

	const CollisionSystem& colSys;

	const InteractionSystem& intSys;
};