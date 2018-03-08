#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <memory>
#include "Component.h"
#include "DisplayLayer.h"

class DisplayComponent : public Component
{
public:
	DisplayComponent();

	void setSFMLShape(sf::Shape & shape);

	void setColor(const sf::Color & color);

	void setDisplayLevel(DisplayLayer::Level level);


	sf::VertexArray & getShape();

	const sf::VertexArray & getShape() const;

	DisplayLayer::Level getDisplayLevel() const;

private:

	sf::VertexArray displayShape;

	DisplayLayer::Level displayLevel = DisplayLayer::Level::Bottom;
};
