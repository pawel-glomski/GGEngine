#include "WorldModule.h"
#include "Utilities/Time/Clock.h"

#include "Systems/CollisionSystem/Collision.h"


class PolygonDisplayShape : public sf::Drawable
{
public:

	PolygonDisplayShape()
	{
		shape.setPrimitiveType(sf::PrimitiveType::LinesStrip);
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(shape, states);
	}

	void copyConfiguration(const PolygonShape & shape)
	{
		setupVertices(shape.vertices, shape.vertCount);
	}

	void setupVertices(const Vec2f* vertices, size_t count)
	{
		shape.clear();
		if (count)
			for (int32_t i = 0; i <= count; ++i)
				shape.append(asVec<sf::Vector2f>(*(vertices + i % count)));
	}

private:

	sf::VertexArray shape;
};




void WorldModule::startUp()
{
}

void WorldModule::update()
{
	world.update(SimulationClock::getDeltaTime());

	static std::vector<PolygonShape> polygons;
	static std::vector<PolygonDisplayShape> shapesDisplays;
	static Transform dynamicShapeTransform;
	static sf::CircleShape contactPoints[2] = {sf::CircleShape(0.1f), sf::CircleShape(0.1f)};

	if (!polygons.size())
	{
		PolygonShape poly;
		poly.setAsBox({ 1.f, 1.f });
		polygons.push_back(poly);
		poly.setAsBox({ 2.f, 1.f });
		polygons.push_back(poly);

		shapesDisplays.resize(2);
		shapesDisplays[0].copyConfiguration(polygons[0]);
		shapesDisplays[1].copyConfiguration(polygons[1]);
		//dynamicShapeTransform.rotation = PI_F / 6.f;
	}
	else
	{
		dynamicShapeTransform.rotation += 0.01f;

		dynamicShapeTransform.position = getDependency<ControllerModule>().getCursorWorldPosition();
		const PolygonShape shape = polygons[0].transformed(dynamicShapeTransform);

		auto collison = polygons[0].collide(dynamicShapeTransform, polygons[1], Transform());
		if (collison.count)
		{
			contactPoints[0].setPosition(asVec<sf::Vector2f>(collison.contact_points[0]));
			contactPoints[1].setPosition(asVec<sf::Vector2f>(collison.contact_points[1]));
			getDependency<DisplayModule>().drawWorldObject(contactPoints[0], Transform(), DisplayLayer::Level::Bottom);
			getDependency<DisplayModule>().drawWorldObject(contactPoints[1], Transform(), DisplayLayer::Level::Bottom);
		}


		//else
		//	std::cout << std::endl;

		getDependency<DisplayModule>().drawWorldObject(shapesDisplays[0], dynamicShapeTransform, DisplayLayer::Level::Bottom);
		getDependency<DisplayModule>().drawWorldObject(shapesDisplays[1], Transform(), DisplayLayer::Level::Bottom);

	}
	
}

void WorldModule::shutdown()
{
	world.entityManager.clear();
}
