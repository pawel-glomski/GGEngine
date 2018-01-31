#include "stdInclude.h"
#include "World.h"

void World::startUp(ControllerManager& controllerManager)
{
	entityManager.startUp();
	
	mainCharacter = entityManager.spawnPermEntity<Character>();
	controllerManager.setCharacterToControl(&mainCharacter->getController());
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
