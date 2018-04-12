#pragma once
#include <memory>
#include "Component.h"
#include "DisplayLayer.h"
#include "ShapeComponent.h"

class DisplayComponent : public Component
{
public:

	DisplayComponent();

	template<class T>
	void setShape(T& shape)
	{
		displayShape.reset();
		displayShape = std::make_unique<T>(shape);
	}

	void setColor(const sf::Color & color);

	void setDisplayLevel(DisplayLayer::Level level);


	ShapeBase& getShape();

	const ShapeBase& getShape() const;

	DisplayLayer::Level getDisplayLevel() const;

	sf::Color getColor() const;

private:

	std::unique_ptr<ShapeBase> displayShape;

	DisplayLayer::Level displayLevel = DisplayLayer::Level::Bottom;
};
