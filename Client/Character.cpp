#include "Character.h"

Character::Character()
{
}

Character::~Character()
{
}

void Character::onSpawn()
{
	CollidableEntity::onSpawn();
	displayShape.setRadius(20);
	displayShape.setFillColor(sf::Color::Blue);
	displayShape.setOutlineColor(sf::Color::Magenta);
	displayShape.setOutlineThickness(3);
}

void Character::display(sf::RenderWindow & window) const
{
	sf::RenderStates states;
	states.transform.translate(globalPosition.x, globalPosition.y);
	window.draw(displayShape, states);
}

void Character::update(float_t deltaTime)
{
	controller.executeActionCommands(*this, deltaTime);
}

Controller & Character::getController()
{
	return controller;
}

const Controller & Character::getController() const
{
	return controller;
}
