#pragma once
#include <SFML/Graphics.hpp>
#include <ECSpp/Component.h>
#include "Utilities/ThirdParty/tinyc2.h"
#include "Utilities/Math/Transform.h"

struct AABB
{
	Vec2f min;
	Vec2f max;
};

class ShapeBase
{
public:
	
	ShapeBase(void* shape, C2_TYPE type);

	virtual ~ShapeBase() = default;

	void setTransform(const Transform& newTransform);


	c2Manifold collisionManifold(const ShapeBase& otherShape) const;

	bool isColliding(const ShapeBase& otherShape) const;

	bool isColliding(void *otherShape, C2_TYPE type, c2x* transform = nullptr) const;


	const Transform& getTransform() const;

	C2_TYPE getType() const;

	AABB getAABB() const;

private:

	virtual void transformShape(const Transform& newTransform) = 0;

protected:

	void* const shape;

	const C2_TYPE type;

	Transform transform;

	AABB aabb;

};




class CircleShape : public ShapeBase
{
public:

	CircleShape();


	void setRadius(float_t newRadius);
	

	const c2Circle& getDetails() const;


private:

	virtual void transformShape(const Transform& newTransform) override;

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

	virtual void transformShape(const Transform& newTransform) override;

	void updateAABB(const Vec2f& newVec);


private:

	c2Poly shape;

	c2Poly staticShape;
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