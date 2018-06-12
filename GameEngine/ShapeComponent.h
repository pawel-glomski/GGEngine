#pragma once
#include <SFML/Graphics.hpp>
#include <ECSpp/Component.h>
#include "tinyc2.h"
#include "Transform.h"


class ShapeBase
{
public:
	
	ShapeBase(void* shape, C2_TYPE type);

	virtual ~ShapeBase() = default;


	void setTransform(const Transform& newTransform);


	c2Manifold collisionManifold(const ShapeBase& otherShape) const;

	bool isColliding(const ShapeBase& otherShape) const;


	const Transform& getTransform() const;

	C2_TYPE getType() const;


private:

	virtual void scaleShape(const Vec2f& scaleV) = 0;


protected:

	void* const shape;

	const C2_TYPE type;

	Transform transform;
};




class CircleShape : public ShapeBase
{
public:

	CircleShape();


	void setRadius(float_t newRadius);
	

	const c2Circle& getDetails() const;


private:

	virtual void scaleShape(const Vec2f& scaleV) override;


private:

	c2Circle shape;
};




class PolygonShape : public ShapeBase
{
public:

	PolygonShape();
	

	void setAsBox(const Vec2f& size);


	void setVertices(const Vec2f* vertices, int count);


	const c2Poly& getDetails() const;

private:

	virtual void scaleShape(const Vec2f& scaleV) override;


private:

	c2Poly shape;
};




class ShapeComponent : public epp::Component
{

public:

	ShapeComponent();


	template<class T>
	T& takeShape()
	{
		shape = std::make_unique<T>();
		return *(T*)shape.get();
	}


	ShapeBase& getShape();

	const ShapeBase& getShape() const;

private:

	std::unique_ptr<ShapeBase> shape;
};