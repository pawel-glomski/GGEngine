#include "CollisionSystem.h"

void CollisionSystem::init(epp::EntityManager & entityManager)
{
	entityManager.requestCGroup(entities);
}

void CollisionSystem::update(epp::EntityManager & entityManager, float dt)
{
	for (auto entity : entities)
	{
		entity.get<ShapeComponent&>().getShape().setTransform(entity.get<TransformComponent&>().getTransform());
		entity.get<CollisionComponent&>().clearCollisions();
	}

	for (auto it = entities.begin(); it != entities.end(); ++it)
	{
		auto entity = *it;
		auto& collisionC = entity.get<CollisionComponent&>();
		auto& shapeC = entity.get<ShapeComponent&>();

		auto it2 = it;
		for (++it2; it2 != entities.end(); ++it2)
		{
			auto entity2 = *it2;
			auto& collisionC2 = entity2.get<CollisionComponent&>();
			auto& shapeC2 = entity2.get<ShapeComponent&>();

			if (collisionC.canCollideWith(collisionC2))
			{
				if (c2Manifold manifold = shapeC.getShape().collisionManifold(shapeC2.getShape()); manifold.count)
				{
					collisionC.addCollision({ it2.getERef(), manifold });
					manifold.n = c2v(-manifold.n.x, -manifold.n.y);
					collisionC2.addCollision({ it.getERef(), manifold });
				}
			}
		}
	}
}