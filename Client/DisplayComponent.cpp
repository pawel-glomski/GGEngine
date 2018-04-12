#include "DisplayComponent.h"
#include "WindowModule.h"


DisplayComponent::DisplayComponent()
{
	setShape(CircleShape());
	//setColor(sf::Color::Red);
}

void DisplayComponent::setColor(const sf::Color & color)
{
	displayShape->setColor(color);
}

void DisplayComponent::setDisplayLevel(DisplayLayer::Level level)
{
	displayLevel = level;
}

ShapeBase& DisplayComponent::getShape()
{
	return *displayShape;
}

const ShapeBase& DisplayComponent::getShape() const
{
	return *displayShape;
}

DisplayLayer::Level DisplayComponent::getDisplayLevel() const
{
	return displayLevel;
}

sf::Color DisplayComponent::getColor() const
{
	//if (displayShape.getVertexCount())
	//	return displayShape[0].color;
	//return sf::Color::Transparent;

	return sf::Color();
}
