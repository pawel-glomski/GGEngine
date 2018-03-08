#include "Character.h"
#include "EntityManager.h"

// for tests
#include "Obstacle.h"

void Character::construct(EntityManager & entityManager)
{
	Entity::construct(entityManager);

	addComponent<DisplayComponent>()->setSFMLShape(sf::CircleShape(0.2f));
	addComponent<ControllerComponent>();
	addComponent<AbilityComponent>();

	getComponent<TransformComponent>()->setGlobalPosition(Vec2f(0, 0));
	getComponent<TransformComponent>()->setGlobalScale(Vec2f(1, 0.6f));
	getComponent<DisplayComponent>()->setDisplayLevel(DisplayLayer::Level::Middle);
	auto circShape = getComponent<DisplayComponent>();
	circShape->setColor(sf::Color::Blue);

	auto & entity = entityManager.spawnEntity<Obstacle>(Entity::Scope::Local, Lifetime::Temp);
	entity->getComponent<RelationComponent>()->attachTo(entityManager.getEntity(getID()));
	entity->getComponent<TransformComponent>()->setRelativePosition(Vec2f(0.2f, 0.2f));
	entity->getComponent<TransformComponent>()->scale(Vec2f(1.f, 1/4.f));

	auto & entity2 = entityManager.spawnEntity<Obstacle>(Entity::Scope::Local, Lifetime::Temp);
	entity2->getComponent<RelationComponent>()->attachTo(entityManager.getEntity(getID()));
	entity2->getComponent<TransformComponent>()->setRelativePosition(Vec2f(1, -2));
	entity2->getComponent<TransformComponent>()->scale(Vec2f(1.f, 10/6.f));

	entity2->getComponent<TransformComponent>()->setMobility(TransformComponent::Mobility::WorldStatic);
	entity2->getComponent<DisplayComponent>()->setColor(sf::Color::Green);

}
