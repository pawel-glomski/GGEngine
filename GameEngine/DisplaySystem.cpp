#include "DisplaySystem.h"

DisplaySystem::DisplaySystem(DisplayModule & displayModule, const CollisionSystem& colSys) : displayModule(displayModule), colSys(colSys)
{}

void DisplaySystem::init(epp::EntityManager & entityManager)
{
	entityManager.requestCGroup(entities);
	entityManager.requestCGroup(entitiesWithCollisions);
}

void DisplaySystem::update(epp::EntityManager & entityManager, float dt)
{
	//drawCollisionGrid();
	//drawCollisions();
	drawEntities();
}

void DisplaySystem::drawEntities()
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

void DisplaySystem::drawCollisions()
{
	for (auto & cPack : entitiesWithCollisions)
		if (auto & collisonC = cPack.get<CollisionComponent&>(); collisonC.getCollisions().size())
			for (auto& collison : collisonC.getCollisions())
			{
				for (size_t i = 0; i < collison.manifold.count; ++i)
				{
					displayModule.drawWorldPoint(collison.manifold.contact_points[i], 0.1f, sf::Color::Cyan);
					displayModule.drawWorldLine(collison.manifold.contact_points[i], collison.manifold.contact_points[i] + collison.manifold.n * 0.2f, sf::Color::Magenta);
				}
			}
}

void DisplaySystem::drawCollisionGrid()
{
	static const sf::Color color(100, 100, 100);
	const float gridSize = colSys.getGrid().getGridSize();
	const float halfGridSize = gridSize * 0.5f;
	for (const auto& cell : colSys.getGrid().getCells())
	{
		Vec2i indicesSigns = signs(cell.first);
		float left = cell.first.x * gridSize - halfGridSize - indicesSigns.x * halfGridSize;
		float top = cell.first.y * gridSize - halfGridSize - indicesSigns.y * halfGridSize;
		float right = cell.first.x * gridSize + halfGridSize - indicesSigns.x * halfGridSize;
		float bottom = cell.first.y * gridSize + halfGridSize - indicesSigns.y * halfGridSize;
		
		displayModule.drawWorldLine(Vec2f(left, top), Vec2f(right, top), color);
		displayModule.drawWorldLine(Vec2f(right, top), Vec2f(right, bottom), color);
		displayModule.drawWorldLine(Vec2f(right, bottom), Vec2f(left, bottom), color);
		displayModule.drawWorldLine(Vec2f(left, bottom), Vec2f(left, top), color);
	}

}
