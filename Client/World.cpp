#include "stdInclude.h"
#include "World.h"

void World::startUp(class InputManager& inputManager)
{
	entityManager.startUp();
	
	mainCharacter = entityManager.spawnPermEntity<Character>();
	inputManager.setInputTargetController(&mainCharacter->getController());
}

void World::shoutDown()
{
	entityManager.shoutDown();
}

void World::display(sf::RenderWindow & window) const
{
	entityManager.display(window);
}

void World::update(float_t deltaTime)
{
	entityManager.updateEntities(deltaTime);
}
