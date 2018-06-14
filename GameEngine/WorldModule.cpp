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
	world.makeSystem<DisplaySystem>(getDependency<DisplayModule>());

	auto bottom = world.entityManager.spawn<DisplayComponent, ShapeComponent, TransformComponent, CollisionComponent, PhysicsComponent>();
	bottom.getComponent<ShapeComponent>()->takeShape<PolygonShape>().setAsBox({ 50.f, 1.f });
	bottom.getComponent<CollisionComponent>()->setCollisionChannels(C_Every & ~C_Static);
	bottom.getComponent<CollisionComponent>()->setCollisionChannel(C_Static);
	bottom.getComponent<PhysicsComponent>()->setMass(0);

	auto left = world.entityManager.spawn<DisplayComponent, ShapeComponent, TransformComponent, CollisionComponent, PhysicsComponent>();
	left.getComponent<ShapeComponent>()->takeShape<PolygonShape>().setAsBox({ 1, 10.f });
	left.getComponent<TransformComponent>()->setPosition(Vec2f(-25.5f, -4.5f));
	left.getComponent<CollisionComponent>()->setCollisionChannels(C_Every & ~C_Static);
	left.getComponent<CollisionComponent>()->setCollisionChannel(C_Static);
	left.getComponent<PhysicsComponent>()->setMass(0);

	auto right = world.entityManager.spawn<DisplayComponent, ShapeComponent, TransformComponent, CollisionComponent, PhysicsComponent>();
	right.getComponent<ShapeComponent>()->takeShape<PolygonShape>().setAsBox({ 1, 10.f });
	right.getComponent<TransformComponent>()->setPosition(Vec2f(25.5f, -4.5f));
	right.getComponent<CollisionComponent>()->setCollisionChannels(C_Every & ~C_Static);
	right.getComponent<CollisionComponent>()->setCollisionChannel(C_Static);
	right.getComponent<PhysicsComponent>()->setMass(0);


	auto middleLeft = world.entityManager.spawn<DisplayComponent, ShapeComponent, TransformComponent, CollisionComponent, PhysicsComponent>();
	middleLeft.getComponent<ShapeComponent>()->takeShape<PolygonShape>().setAsBox({ 0.2f, 3.f });
	middleLeft.getComponent<TransformComponent>()->setPosition(Vec2f(-2.5f, -4.5f));
	middleLeft.getComponent<TransformComponent>()->rotate(PI_F / 3.f);
	middleLeft.getComponent<CollisionComponent>()->setCollisionChannels(C_Every & ~C_Static);
	middleLeft.getComponent<CollisionComponent>()->setCollisionChannel(C_Static);
	middleLeft.getComponent<PhysicsComponent>()->setMass(0);

	auto middleRight = world.entityManager.spawn<DisplayComponent, ShapeComponent, TransformComponent, CollisionComponent, PhysicsComponent>();
	middleRight.getComponent<ShapeComponent>()->takeShape<PolygonShape>().setAsBox({ 0.2f, 3.f });
	middleRight.getComponent<TransformComponent>()->setPosition(Vec2f(2.5f, -4.5f));
	middleRight.getComponent<TransformComponent>()->rotate(-PI_F / 3.f);
	middleRight.getComponent<CollisionComponent>()->setCollisionChannels(C_Every & ~C_Static);
	middleRight.getComponent<CollisionComponent>()->setCollisionChannel(C_Static);
	middleRight.getComponent<PhysicsComponent>()->setMass(0);
}

void WorldModule::update()
{
	world.update(SimulationClock::getDeltaTime());
}

void WorldModule::shutdown()
{
}
