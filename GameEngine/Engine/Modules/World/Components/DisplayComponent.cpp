#include "DisplayComponent.h"
#include "Modules/Window/WindowModule.h"

DisplayShape::DisplayShape(C2_TYPE shapeType) : type(shapeType)
{
}

C2_TYPE DisplayShape::getType() const
{
	return type;
}


CircleDisplayShape::CircleDisplayShape() : DisplayShape(C2_TYPE::C2_CIRCLE)
{
	static const uint8_t vertices = 30;
	static const float step = 2*PI_F / vertices;

	shape.setPrimitiveType(sf::PrimitiveType::LinesStrip);
	shape.append(sf::Vector2f());
	for (uint8_t i = 0; i <= vertices; ++i)
		shape.append(sf::Vector2f(std::cosf(step * i), std::sinf(step * i)));
}

void CircleDisplayShape::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform.scale(radius, radius);
	target.draw(shape, states);
}

bool CircleDisplayShape::copyConfiguration(const ShapeBase & shapeToCpy)
{
	if (shapeToCpy.getType() == C2_TYPE::C2_CIRCLE)
	{
		const CircleShape& castedShapeToCpy = static_cast<const CircleShape&>(shapeToCpy);
		setRadius(castedShapeToCpy.getDetails().r);
		return true;
	}
	return false;
}

void CircleDisplayShape::setRadius(float radius)
{
	this->radius = radius;
}




PolygonDisplayShape::PolygonDisplayShape() : DisplayShape(C2_TYPE::C2_POLY)
{
	shape.setPrimitiveType(sf::PrimitiveType::LinesStrip);
}

void PolygonDisplayShape::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(shape, states);
}

bool PolygonDisplayShape::copyConfiguration(const ShapeBase & shapeToCpy)
{
	if (shapeToCpy.getType() == C2_TYPE::C2_POLY)
	{
		const PolygonShape& castedShapeToCpy = static_cast<const PolygonShape&>(shapeToCpy);
		setupVertices(castedShapeToCpy.getDetails().verts, castedShapeToCpy.getDetails().count);

		return true;
	}
	return false;
}

const sf::VertexArray & PolygonDisplayShape::getVertexArray() const
{
	return shape;
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
			displayShape = std::move(newShape);
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

