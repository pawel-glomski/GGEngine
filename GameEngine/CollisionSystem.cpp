#include "CollisionSystem.h"

void CollisionSystem::init(epp::EntityManager & entityManager)
{
	entityManager.requestCGroup(entities);
}

void CollisionSystem::update(epp::EntityManager & entityManager, float dt)
{
	entities.begin().getERefPtr().getComponent<TransformComponent>()->setPosition(Vec2f(-sf::Mouse::getPosition().y + 500, sf::Mouse::getPosition().x - 850) / 100.f);
	for (auto pack : entities)
	{
		pack.get<ShapeComponent&>().getShape().setTransform(pack.get<TransformComponent&>().getTransform());
		pack.get<CollisionComponent&>().clearCollisions();
	}

	for (auto it = entities.begin(); it != entities.end(); ++it)
	{
		auto pack = *it;
		auto& collisionC = pack.get<CollisionComponent&>();
		auto& shapeC = pack.get<ShapeComponent&>();

		auto it2 = it;
		for (++it2; it2 != entities.end(); ++it2)
		{
			if (it2 == it)
				continue;

			auto pack2 = *it2;
			auto& collisionC2 = pack2.get<CollisionComponent&>();
			auto& shapeC2 = pack2.get<ShapeComponent&>();

			if (collisionC.canCollideWith(collisionC2))
			{
				c2Manifold manifold = shapeC.getShape().collisionManifold(shapeC2.getShape());
				if (manifold.count)
				{
					collisionC.addCollision({ it.getERefPtr(), asVec<Vec2f>(manifold.contact_points[0]), asVec<Vec2f>(manifold.n), manifold.depths[0] });
					collisionC2.addCollision({ it.getERefPtr(), asVec<Vec2f>(manifold.contact_points[0]), -asVec<Vec2f>(manifold.n), manifold.depths[0] });
				}
			}
		}
	}
}
