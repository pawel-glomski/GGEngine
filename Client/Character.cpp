#include "Character.h"

Character::Character()
{
	displayShape.setRadius(30);
	displayShape.setFillColor(sf::Color::Blue);
	displayShape.setOutlineColor(sf::Color::Green);
	displayShape.setOutlineThickness(4);
	displayShape.setOrigin(displayShape.getRadius(), displayShape.getRadius());
}

Character::~Character()
{
}

void Character::display(sf::RenderWindow & window) const
{
	sf::RenderStates states;
	sf::RectangleShape debugDirection;
	debugDirection.setSize(sf::Vector2f(displayShape.getRadius(), 1));

	auto globalPos = getGlobalPosition();
	states.transform.translate(globalPos.x, globalPos.y);
	states.transform.rotate(relativeTransform.getRotation() / PI_F * 180);
	window.draw(displayShape, states);
	window.draw(debugDirection, states);
}

void Character::update(float_t deltaTime)
{
	controller.controlCharacter(*this, deltaTime);
}

Controller & Character::getController()
{
	return controller;
}

const Controller & Character::getController() const
{
	return controller;
}
