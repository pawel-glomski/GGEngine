#include "ShapeComponent.h"
#include "DisplayModule.h"

void ShapeBase::collideWith(ShapeBase & otherShape)
{
	//c2Manifold manifold;
	//c2Collide(getC2Shape(), &transformC2, shapeType, otherShape.getC2Shape(), &otherShape.transformC2, otherShape.shapeType, &manifold);
}

void ShapeBase::setTransform(const Transform & newTransform)
{
	//transformC2 = c2Transform({ newTransform.position.x, newTransform.position.y }, newTransform.rotation);
}
//
//C2ShapeType ShapeBase::getShapeType() const
//{
//	return shapeType;
//}




CircleShape::CircleShape(float_t radius) /*: ShapeBase(C2ShapeType::Circle)*/
{
	setRadius(radius);
}

void CircleShape::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(displayShape, states);
}

void CircleShape::setRadius(float_t newRadius)
{
	//c2Shape.r = newRadius;
	displayShape.setRadius(newRadius);
}

void CircleShape::setColor(const sf::Color & color)
{
	displayShape.setFillColor(color);
}

float_t CircleShape::getRadius() const
{
	//return c2Shape.r;
	return 0;
}

void * CircleShape::getC2Shape() const
{
	//return (void*)&c2Shape;
	return nullptr;
}




CapsuleShape::CapsuleShape(float_t radius, float_t length) /*: ShapeBase(C2ShapeType::Capsule)*/
{
	setLength(radius);
	setRadius(length);
}

void CapsuleShape::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	//sf::Transform baseTransform = states.transform;
	//target.draw(displayLine, states);

	//states.transform.translate(sf::Vector2f(c2Shape.a.x, c2Shape.a.y));
	//target.draw(displayCircle, states);

	//states.transform = baseTransform;

	//states.transform.translate(sf::Vector2f(c2Shape.b.x, c2Shape.b.y));
	//target.draw(displayCircle, states);
}

void CapsuleShape::setLength(float_t length)
{
	//this->length = length;
	//c2Shape.a = { 0.f, -length / 2.f };
	//c2Shape.b = { 0.f, length / 2.f };
	//displayLine.setSize({ displayLine.getSize().x, length });
	//displayLine.setOrigin(displayLine.getSize() / 2.f);
}

void CapsuleShape::setRadius(float_t radius)
{
	//c2Shape.r = radius;
	//displayCircle.setRadius(radius);
	//displayCircle.setOrigin({ radius, radius });
	//displayLine.setSize({ radius * 2.f, displayLine.getSize().y });
	//displayLine.setOrigin(displayLine.getSize() / 2.f);
}

void CapsuleShape::setColor(const sf::Color & color)
{
	displayCircle.setFillColor(color);
	displayLine.setFillColor(color);
}

float_t CapsuleShape::getLength() const
{
	return displayLine.getSize().y;
}

float_t CapsuleShape::getRadius() const
{
	return displayCircle.getRadius();
}

void * CapsuleShape::getC2Shape() const
{
	return nullptr;
}



RectangleShape::RectangleShape(const Vec2f & size)/* : ShapeBase(C2ShapeType::Poly)*/
{
	//c2Shape.count = 4;
	//setSize(size);
	//c2MakePoly(&c2Shape);
}

void RectangleShape::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(displayShape, states);
}

void RectangleShape::setSize(const Vec2f & size)
{
	//c2Shape.verts[0] = { size.x / 2.f, -size.y / 2.f };
	//c2Shape.verts[1] = { size.x / 2.f, size.y / 2.f };
	//c2Shape.verts[2] = { -size.x / 2.f, size.y / 2.f };
	//c2Shape.verts[3] = { -size.x / 2.f, -size.y / 2.f };
	//displayShape.setSize(size.asSfVec());
}

void RectangleShape::setColor(const sf::Color & color)
{
	displayShape.setFillColor(color);
}

Vec2f RectangleShape::getSize() const
{
	return Vec2f(displayShape.getSize());
}

void * RectangleShape::getC2Shape() const
{
	return nullptr;
}
