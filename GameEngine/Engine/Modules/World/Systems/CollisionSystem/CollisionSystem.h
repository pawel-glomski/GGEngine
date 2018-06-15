#pragma once
#include <ECSpp/System.h>
#include "Modules/World/Components/CollisionComponent.h"
#include "Modules/World/Components/TransformComponent.h"
#include "Modules/World/Components/ShapeComponent.h"
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

	size_t checkedEntitiesCount = 0;

	Grid grid;
};