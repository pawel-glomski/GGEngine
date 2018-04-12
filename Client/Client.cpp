#include "Client.h"

#include "PlayerCharacter.h"


void Client::play()
{
	modules.startUp();
	auto& mainEntity = modules.getModule<ObjectModule>().spawnObject<PlayerCharacter>(IdScope::Global, Lifetime::Perm);
	modules.getModule<ControllerModule>().setControlledEntity(mainEntity.getComponentPtr<ControllerComponent>());
	modules.getModule<DisplayModule>().setWatchedEntity(mainEntity.getComponent<SkeletonComponent>().getJoint(JointIndex::Root).get<CPtr_t<TransformComponent>>());

	auto & entity = modules.getModule<ObjectModule>().spawnObject<BasicObject<TransformComponent, DisplayComponent>>(IdScope::Global, Lifetime::Perm);
	//mainEntity.attach(entity);
	entity.getComponent<DisplayComponent>().setColor(sf::Color::Green);
	entity.getComponent<DisplayComponent>().setShape(RectangleShape());
	entity.getComponent<TransformComponent>().setRelativePosition({ 2.f,2.f });

	//for (size_t i = 0; i < 1000; i++)
	//{
	//	auto & entity = modules.getModule<ObjectModule>().spawnObject<WorldObject<DisplayComponent>>(IdScope::Global, Lifetime::Perm);
	//	entity.getComponent<TransformComponent>()->rotate(0.1f + i * 0.01f);
	//	entity.getComponent<TransformComponent>()->moveForward(i * 0.1f);
	//}

	while(modules.getModule<WindowModule>().getWin().isOpen())
		modules.update(clock.getDeltaTime());

	modules.shutdown();
}