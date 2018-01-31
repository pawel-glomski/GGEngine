#pragma once
#include "Character.h"
#include "EntityManager.h"

class World
{
public:

	void display(sf::RenderWindow& window) const;
	void update(float_t deltaTime);
	void startUp(ControllerManager& controllerManager);
	void shoutDown();

private:
	EntityManager entityManager;
	Character* mainCharacter;
};

