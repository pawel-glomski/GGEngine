#include "WorldModule.h"
#include "Clock.h"

#include "DisplaySystem.h"
#include "CollisionSystem.h"
#include "PhysicsSystem.h"

void WorldModule::startUp()
{
	world.makeSystem<CollisionSystem>();
	world.makeSystem<PhysicsSystem>();
	world.makeSystem<DisplaySystem>(getDependency<DisplayModule>());

	auto entity = world.entityManager.spawn<DisplayComponent, ShapeComponent, TransformComponent, CollisionComponent, PhysicsComponent>();
	entity.getComponent<ShapeComponent>()->takeShape<PolygonShape>().setAsBox({ 5.f, 1.f });

	auto entity2 = world.entityManager.spawn<DisplayComponent, ShapeComponent, TransformComponent, CollisionComponent, PhysicsComponent>();
	entity2.getComponent<TransformComponent>()->moveGlobal({ 0, 2.f });
}

void WorldModule::update()
{
	world.update(SimulationClock::getDeltaTime());
}

void WorldModule::shutdown()
{
}
