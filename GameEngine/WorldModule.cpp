#include "WorldModule.h"
#include "Clock.h"

#include "DisplaySystem.h"
#include "CollisionSystem.h"
#include "PhysicsSystem.h"
#include "InteractionSystem.h"

void WorldModule::startUp()
{
	world.makeSystem<CollisionSystem>();
	world.makeSystem<InteractionSystem>(getDependency<ControllerModule>());
	world.makeSystem<PhysicsSystem>();
	world.makeSystem<DisplaySystem>(getDependency<DisplayModule>(), world.getSystem<CollisionSystem>());

	float edgeSize = 500;

	auto bottom = world.entityManager.spawn<DisplayComponent, ShapeComponent, TransformComponent, CollisionComponent, PhysicsComponent>();
	bottom.getComponent<ShapeComponent>()->takeShape<PolygonShape>().setAsBox({ edgeSize, 3.f });
	bottom.getComponent<CollisionComponent>()->setCollisionChannels(C_Every & ~C_Static);
	bottom.getComponent<CollisionComponent>()->setCollisionChannel(C_Static);
	bottom.getComponent<PhysicsComponent>()->setMass(0);

	auto left = world.entityManager.spawn<DisplayComponent, ShapeComponent, TransformComponent, CollisionComponent, PhysicsComponent>();
	left.getComponent<ShapeComponent>()->takeShape<PolygonShape>().setAsBox({ 3, edgeSize });
	left.getComponent<TransformComponent>()->setPosition(Vec2f(-edgeSize / 2.f, -edgeSize / 2.f));
	left.getComponent<CollisionComponent>()->setCollisionChannels(C_Every & ~C_Static);
	left.getComponent<CollisionComponent>()->setCollisionChannel(C_Static);
	left.getComponent<PhysicsComponent>()->setMass(0);

	auto right = world.entityManager.spawn<DisplayComponent, ShapeComponent, TransformComponent, CollisionComponent, PhysicsComponent>();
	right.getComponent<ShapeComponent>()->takeShape<PolygonShape>().setAsBox({ 3, edgeSize });
	right.getComponent<TransformComponent>()->setPosition(Vec2f(edgeSize / 2.f, -edgeSize / 2.f));
	right.getComponent<CollisionComponent>()->setCollisionChannels(C_Every & ~C_Static);
	right.getComponent<CollisionComponent>()->setCollisionChannel(C_Static);
	right.getComponent<PhysicsComponent>()->setMass(0);

	auto top = world.entityManager.spawn<DisplayComponent, ShapeComponent, TransformComponent, CollisionComponent, PhysicsComponent>();
	top.getComponent<ShapeComponent>()->takeShape<PolygonShape>().setAsBox({ edgeSize, 3.f });
	top.getComponent<TransformComponent>()->setPosition(Vec2f(0, -edgeSize));
	top.getComponent<CollisionComponent>()->setCollisionChannels(C_Every & ~C_Static);
	top.getComponent<CollisionComponent>()->setCollisionChannel(C_Static);
	top.getComponent<PhysicsComponent>()->setMass(0);
}

void WorldModule::update()
{
	world.update(SimulationClock::getDeltaTime());
}

void WorldModule::shutdown()
{
}
