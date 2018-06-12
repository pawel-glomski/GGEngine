#include "DisplayComponent.h"
#include "WindowModule.h"



std::size_t sf::PolygonShape::getPointCount() const
{
	return verticesCount;
}

sf::Vector2f sf::PolygonShape::getPoint(std::size_t index) const
{
	return asVec<sf::Vector2f>(vertices[index]);
}




DisplayShape::DisplayShape(sf::Shape & shape, C2_TYPE shapeType) : shapeRef(shape), type(shapeType)
{
}

void DisplayShape::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(shapeRef, states);
}

void DisplayShape::copyConfiguration(const sf::Shape & shape)
{
	this->shapeRef = shape;
}

C2_TYPE DisplayShape::getType() const
{
	return type;
}

const sf::Shape & DisplayShape::getSfShape() const
{
	return shapeRef;
}



CircleDisplayShape::CircleDisplayShape() : DisplayShape(shape, C2_TYPE::C2_CIRCLE)
{
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::White);
	shape.setOutlineThickness(0.01f);
}

bool CircleDisplayShape::copyConfiguration(const ShapeBase & shapeToCpy)
{
	if (shapeToCpy.getType() == C2_TYPE::C2_CIRCLE)
	{
		const CircleShape& castedShapeToCpy = static_cast<const CircleShape&>(shapeToCpy);
		shape.setRadius(castedShapeToCpy.getDetails().r);
		shape.setOrigin(shape.getRadius(), shape.getRadius());
		return true;
	}
	return false;
}




PolygonDisplayShape::PolygonDisplayShape() : DisplayShape(shape, C2_TYPE::C2_POLY)
{
}

bool PolygonDisplayShape::copyConfiguration(const ShapeBase & shapeToCpy)
{
	if (shapeToCpy.getType() == C2_TYPE::C2_POLY)
	{
		const PolygonShape& castedShapeToCpy = static_cast<const PolygonShape&>(shapeToCpy);
		shape.setupVertices(castedShapeToCpy.getDetails().verts, castedShapeToCpy.getDetails().count);

		return true;
	}
	return false;
}




DisplayComponent::DisplayComponent()
{
	displayShape = std::make_unique<CircleDisplayShape>();
}

void DisplayComponent::takeShape(const ShapeBase & shape)
{
	if (displayShape->getType() != shape.getType())
	{
		std::unique_ptr<DisplayShape> newShape;

		if (shape.getType() == C2_TYPE::C2_CIRCLE)
			newShape = std::make_unique<CircleDisplayShape>();
		else if (shape.getType() == C2_TYPE::C2_POLY)
			newShape = std::make_unique<PolygonDisplayShape>();

		if (newShape)
		{
			newShape->copyConfiguration(displayShape->getSfShape());
		
			displayShape = std::move(newShape);
		}
		else
			ASSERT(newShape, "Used unsupported shape type");
	}

	displayShape->copyConfiguration(shape);
}

void DisplayComponent::setDisplayLevel(DisplayLayer::Level level)
{
	displayLevel = level;
}

DisplayShape& DisplayComponent::getShape()
{
	return *displayShape;
}

const DisplayShape& DisplayComponent::getShape() const
{
	return *displayShape;
}

DisplayLayer::Level DisplayComponent::getDisplayLevel() const
{
	return displayLevel;
}

