#pragma once
#include "Singleton.h"
#include "Character.h"
#include "EntityManager.h"

class World
{
public:

	void display(sf::RenderWindow& window) const;
	void update(float_t deltaTime);
	void startUp(class InputManager& inputManager);
	void shoutDown();

private:
	EntityManager entityManager;
	Character* mainCharacter;
};

