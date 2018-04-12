#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "b2Collision.h"
#include "Transform.h"


class ShapeBase : public sf::Drawable
{
public:
	
	//ShapeBase(C2ShapeType shapeType) : shapeType(shapeType)
	//{}

	virtual ~ShapeBase() = default;

	
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const override = 0;


	void collideWith(ShapeBase& otherShape);


	virtual void setTransform(const Transform& newTransform);


	virtual void setColor(const sf::Color& newColor) = 0;


	//C2ShapeType getShapeType() const;


private:

	virtual void* getC2Shape() const = 0;


protected:

	//const C2ShapeType shapeType;

	//c2x transformC2;
};

template<class T>
class Shape
{

protected:

	T c2Shape;
};



class CircleShape : public ShapeBase
{
public:

	CircleShape(float_t radius = 1.f);


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


	void setRadius(float_t newRadius);


	virtual void setColor(const sf::Color& color) override;


	float_t getRadius() const;

private:

	virtual void* getC2Shape() const override;

private:

	//c2Circle c2Shape;
	b2CircleShape test;
	sf::CircleShape displayShape;

};

class CapsuleShape : public ShapeBase
{
public:

	CapsuleShape(float_t radius = 1.f, float_t length = 2.f);


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


	// distance between circles
	void setLength(float_t length);

	void setRadius(float_t radius);


	virtual void setColor(const sf::Color& color) override;


	float_t getLength() const;

	float_t getRadius() const;

private:

	virtual void* getC2Shape() const override;

private:

	sf::CircleShape displayCircle;

	sf::RectangleShape displayLine;

	//c2Capsule c2Shape;

	float_t length;
};

class RectangleShape : public ShapeBase
{
public:
	
	RectangleShape(const Vec2f& size = Vec2f(1.f, 1.f));


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


	void setSize(const Vec2f& size);


	virtual void setColor(const sf::Color& color) override;


	Vec2f getSize() const;


private:

	virtual void* getC2Shape() const override;

private:

	//c2Poly c2Shape;

	sf::RectangleShape displayShape;
};

class PolygonShape : public ShapeBase
{
	PolygonShape() /*: ShapeBase(C2ShapeType::Poly)*/
	{}

private:

	Vec2f vertices[8];
};