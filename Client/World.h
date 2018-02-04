#pragma once
#include "Character.h"
#include "EntityManager.h"
#include "Singleton.h"

class World : public Singleton<World>
{
public:
	void display(sf::RenderWindow& window) const;
	void update(float_t deltaTime);
	void startUp(ControllerManager& controllerManager);
	void shoutDown();

private:
	Character* mainCharacter = nullptr;
	EntityManager entityManager;
};

