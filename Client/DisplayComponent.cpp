#include "stdInclude.h"
#include "DisplayComponent.h"

DisplayComponent::DisplayComponent()
{
	setSFMLShape(sf::CircleShape());
	displayShape.setPrimitiveType(sf::PrimitiveType::TriangleFan);
}

void DisplayComponent::setSFMLShape(sf::Shape & shape)
{
	sf::Color color;
	if (displayShape.getVertexCount())
		color = displayShape[0].color;
	displayShape.clear();
	sf::Vector2f originOffset(shape.getLocalBounds().width / 2.f, shape.getLocalBounds().height / 2.f);

	for (uint8_t i = 8; i <= shape.getPointCount() + 8; i++)
		displayShape.append(shape.getPoint(i % shape.getPointCount()) - originOffset);
	setColor(color);
}

void DisplayComponent::setColor(const sf::Color & color)
{
	for (uint8_t i = 0; i < displayShape.getVertexCount(); i++)
		displayShape[i].color = color;
}

void DisplayComponent::setDisplayLevel(DisplayLayer::Level level)
{
	displayLevel = level;
}

sf::VertexArray & DisplayComponent::getShape()
{
	return displayShape;
}

const sf::VertexArray & DisplayComponent::getShape() const
{
	return displayShape;
}

DisplayLayer::Level DisplayComponent::getDisplayLevel() const
{
	return displayLevel;
}
