#include "WorldModule.h"
#include "Clock.h"

#include "DisplaySystem.h"
#include "CollisionSystem.h"

void WorldModule::startUp()
{
	world.makeSystem<CollisionSystem>();
	world.makeSystem<DisplaySystem>(getDependency<DisplayModule>());

	auto entity = world.entityManager.spawn<DisplayComponent, ShapeComponent, TransformComponent>();
	entity.getComponent<ShapeComponent>()->takeShape<PolygonShape>().setAsBox({ 5.f, 1.f });
}

void WorldModule::update()
{
	world.update(SimulationClock::getDeltaTime());
}

void WorldModule::shutdown()
{
}
