#include "DisplaySystem.h"

DisplaySystem::DisplaySystem(DisplayModule & displayModule) : displayModule(displayModule)
{
}

void DisplaySystem::init(epp::EntityManager & entityManager)
{
	entityManager.requestCGroup(entities);
}

void DisplaySystem::update(epp::EntityManager & entityManager, float dt)
{

	for (auto & cPack : entities)
	{
		auto & displayC = cPack.get<DisplayComponent&>();
		auto & shapeC = cPack.get<ShapeComponent&>();
		auto & transformC = cPack.get<TransformComponent&>();
		auto & collisonC = cPack.get<CollisionComponent&>();

		displayC.takeShape(shapeC.getShape());

		if (collisonC.getCollisions().size())
			for (auto& collison : collisonC.getCollisions())
			{
				displayModule.drawWorldPoint(collison.collisionPoint, 0.1f, sf::Color::Cyan);
				displayModule.drawWorldLine(collison.collisionPoint, collison.collisionPoint + collison.normal * 0.2f, sf::Color::Magenta);
			}
		displayModule.drawWorldObject(displayC.getShape(), transformC.getTransform(), displayC.getDisplayLevel());
	}
}