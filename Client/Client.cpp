#include <SFML/Network.hpp>
#include "Client.h"
#include "MemoryManager.h"
#include "DisplaySystem.h"
#include "AbilitySystem.h"
#include "LifetimeSystem.h"
#include "Obstacle.h"

void Client::play()
{
	startUp();

	float_t deltaTime = 0;
	std::chrono::high_resolution_clock::time_point last = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::time_point now = last;

	float_t dtSum = 0;

	while(displayManager->getWin()->isOpen())
	{
		rawInputReceiver.catchInput(displayManager->getWin());

		playerController.feedRawInput(rawInputReceiver.getCurrentInput());

		deltaTime = calcDeltaTime(now, last);

		entityManager.update(deltaTime);

		displayManager->display(getSystem<DisplaySystem>());

	}
	shoutDown();
}

void Client::startUp()
{
	MemoryManager::startUp();
	(displayManager = std::shared_ptr<DisplayManager>(MemoryManager::stack.allocObject<DisplayManager>(), MemoryManager::StackDeleter<DisplayManager>()))->startUp();
	playerController.startUp();
	entityManager.startUp();
	systemsStartUp();

	// this data should be obtained from server
	{
		auto & mainChar = entityManager.spawnEntity<Character>(Entity::Scope::Global, Lifetime::Perm);
		auto & cam = entityManager.spawnEntity<Camera>(Entity::Scope::Local, Lifetime::Perm);
		cam->getComponent<RelationComponent>()->attachTo(mainChar);

		playerController.setControlledEntity(mainChar);
		getSystem<DisplaySystem>()->setCamera(cam);

		auto mainCharAbilityComp = mainChar->getComponent<AbilityComponent>();
		// this may be set as default in AbilityComponent constructor, but maybe there will be different walking abilities
		mainCharAbilityComp->abilitySet[(uint8_t)ControllerAction::MoveForward] = Ability::getStaticInstanceByGlobalID(1);
		mainCharAbilityComp->abilitySet[(uint8_t)ControllerAction::MoveBackward] = Ability::getStaticInstanceByGlobalID(2);
		mainCharAbilityComp->abilitySet[(uint8_t)ControllerAction::MoveLeft] = Ability::getStaticInstanceByGlobalID(3);
		mainCharAbilityComp->abilitySet[(uint8_t)ControllerAction::MoveRight] = Ability::getStaticInstanceByGlobalID(4);
		mainCharAbilityComp->abilitySet[(uint8_t)ControllerAction::FirstAbility] = Ability::getStaticInstanceByGlobalID(5);

		for (size_t i = 0; i < 500; i++)
		{
			auto & obstacle = entityManager.spawnEntity<Obstacle>(Entity::Scope::Global, Lifetime::Perm);
			obstacle->getComponent<TransformComponent>()->setGlobalPosition(Vec2f(-50.f + (float_t)(rand() % 100), -50.f + (float_t)(rand() % 100)));
			obstacle->getComponent<TransformComponent>()->setMobility(TransformComponent::Mobility::WorldStatic);
		}
	}
}

void Client::systemsStartUp()
{
	// order matters here!
	entityManager.addSystem(makeSystem<LifetimeSystem>());		// first check if entity is should be spawned/killed
	entityManager.addSystem(makeSystem<AbilitySystem>());		// then execute action commands on entities
	entityManager.addSystem(makeSystem<DisplaySystem>());		// then apply transform changes to display components

	getSystem<DisplaySystem>()->startUp(displayManager);
}

void Client::shoutDown()
{
	systemsShoutDown();
	entityManager.shoutDown();
	playerController.shoutDown();
	displayManager->shoutDown();
	displayManager.reset();

	MemoryManager::shoutDown();
}

void Client::systemsShoutDown()
{
	getSystem<DisplaySystem>()->shoutDown();
	entityUpdateSystems.clear();
}

float Client::calcDeltaTime(std::chrono::high_resolution_clock::time_point & now, std::chrono::high_resolution_clock::time_point & last)
{
	static float_t dtSum = 0;
	static uint32_t frames = 0;
	float dt = 0.f;
	now = std::chrono::high_resolution_clock::now();
	dt = (now - last).count() / 1000000000.f;
	last = now;
	// average fps
	{
		dtSum += dt;
		frames++;
		displayManager->getWin()->setTitle("Client. FPS = " + std::to_string(1.f / (dtSum / frames)));
		if (dtSum > 5)
		{
			dtSum = 0;
			frames = 0;
		}
	}
	return dt;
}