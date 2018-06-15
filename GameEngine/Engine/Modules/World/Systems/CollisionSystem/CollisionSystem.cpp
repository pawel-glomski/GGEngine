#include "CollisionSystem.h"

void CollisionSystem::init(epp::EntityManager & entityManager)
{
	entityManager.requestCGroup(entities);
}

void CollisionSystem::update(epp::EntityManager & entityManager, float dt)
{
	updateGrid();
	findCollisions();
}

void CollisionSystem::updateGrid()
{
	checkedEntitiesCount = 0;
	grid.clear();
	for (auto it = entities.begin(); it != entities.end(); )
	{
		if (it.getComponent<TransformComponent>().getPosition().y >= 1000.f)
		{
			it.getERef().die();
			if (!it.isValid())
				++it;
		}
		else
		{
			grid.insert(it);
			++it;
			++checkedEntitiesCount;
		}
	}
	std::cout << checkedEntitiesCount << std::endl;
}

void CollisionSystem::findCollisions()
{
	for (auto it = entities.begin(); it != entities.end(); ++it)
	{
		it.getComponent<ShapeComponent>().getShape().setTransform(it.getComponent<TransformComponent>().getTransform());
		it.getComponent<CollisionComponent>().clearCollisions();
	}

	for (auto it = entities.begin(); it != entities.end(); ++it)
	{
		auto& collisionC = it.getComponent<CollisionComponent>();
		auto& shapeC = it.getComponent<ShapeComponent>();

		for (auto vecPtr : grid.queryFor(it.getComponent<TransformComponent>().getPosition(), shapeC.getShape().getAABB()))
			for (auto otherEntityIt : *vecPtr)
			{
				if (otherEntityIt == it)
					continue;

				auto& collisionC2 = otherEntityIt.getComponent<CollisionComponent>();
				auto& shapeC2 = otherEntityIt.getComponent<ShapeComponent>();

				if (collisionC.canCollideWith(collisionC2))
				{
					if (c2Manifold manifold = shapeC.getShape().collisionManifold(shapeC2.getShape()); manifold.count)
					{
						collisionC.addCollision({ otherEntityIt.getERef(), manifold });
						manifold.n = c2v(-manifold.n.x, -manifold.n.y);
						collisionC2.addCollision({ it.getERef(), manifold });
					}
				}
			}
	}
}

const Grid& CollisionSystem::getGrid() const
{
	return grid;
}