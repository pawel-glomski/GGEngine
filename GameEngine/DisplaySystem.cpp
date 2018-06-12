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

		displayC.takeShape(shapeC.getShape());

		displayModule.drawWorldObject(displayC.getShape(), transformC.getTransform(), displayC.getDisplayLevel());
	}
}