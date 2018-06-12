#include "Obstacle.h"
#include "DisplayComponent.h"
#include "TransformComponent.h"

void Obstacle::construct(EntityManager & entityManager)
{
	Entity::construct(entityManager);
	addComponent<DisplayComponent>()->setSFMLShape(sf::RectangleShape(sf::Vector2f(0.5, 0.5)));
	getComponent<DisplayComponent>()->setColor(sf::Color::Red);
}
