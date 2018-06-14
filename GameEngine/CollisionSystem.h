#pragma once
#include "ECSpp/System.h"
#include "CollisionComponent.h"
#include "TransformComponent.h"
#include "ShapeComponent.h"
#include "Grid.h"

class CollisionSystem : public epp::System
{
public:
	
	virtual void init(epp::EntityManager& entityManager) override;

	virtual void update(epp::EntityManager& entityManager, float dt) override;


	const Grid& getGrid() const;

private:

	void updateGrid();

	void findCollisions();

private:

	epp::CGroup<CollisionComponent, ShapeComponent, TransformComponent> entities;

	Grid grid;
};