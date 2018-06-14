#include "ShapeComponent.h"
#include "DisplayModule.h"

#define CUTE_C2_IMPLEMENTATION
#include "tinyc2.h"

ShapeBase::ShapeBase(void * shape, C2_TYPE type) : shape(shape), type(type)
{}

c2Manifold ShapeBase::collisionManifold(const ShapeBase & otherShape) const
{
	c2Manifold manifold;
	c2Collide(shape, NULL, type, otherShape.shape, NULL, otherShape.type, &manifold);
	return manifold;
}

bool ShapeBase::isColliding(const ShapeBase & otherShape) const
{
	return c2Collided(shape, NULL, type, otherShape.shape, NULL, otherShape.type);
}

bool ShapeBase::isColliding(void * otherShape, C2_TYPE type, c2x * transform) const
{
	return c2Collided(shape, NULL, this->type, otherShape, transform, type);
}

void ShapeBase::setTransform(const Transform& newTransform)
{
	if (transform != newTransform)
	{
		transformShape(newTransform);
		transform = newTransform;
	}
}

const Transform & ShapeBase::getTransform() const
{
	return transform;
}

C2_TYPE ShapeBase::getType() const
{
	return type;
}

AABB ShapeBase::getAABB() const
{
	return aabb;
}



CircleShape::CircleShape() : ShapeBase(&shape, C2_TYPE::C2_CIRCLE)
{
}

void CircleShape::setRadius(float_t newRadius)
{
	shape.r = newRadius;
	aabb.min = Vec2f(-newRadius, -newRadius);
	aabb.max = Vec2f(newRadius, newRadius);
}

const c2Circle & CircleShape::getDetails() const
{
	return shape;
}

void CircleShape::transformShape(const Transform& newTransform)
{
	shape.p = asVec<c2v>(newTransform.position);
	setRadius(shape.r * newTransform.scale.x / transform.scale.x);
}



PolygonShape::PolygonShape() : ShapeBase(&shape, C2_TYPE::C2_POLY)
{
}

void PolygonShape::setAsBox(const Vec2f & size)
{
	transform.rotation = 0.f;
	transform.scale = Vec2f::OneVector;

	Vec2f vertices[4];

	Vec2f halfSize(size * 0.5f);

	vertices[0] = -halfSize;
	vertices[1] = { halfSize.x, -halfSize.y };
	vertices[2] = halfSize;
	vertices[3] = { -halfSize.x, halfSize.y };

	setVertices(vertices, 4);
}

void PolygonShape::setVertices(const Vec2f* vertices, int count)
{
	if (!count)
		return;

	ASSERT((count <= C2_MAX_POLYGON_VERTS), "Vertices count cannot be greater b2_maxPolygonVertices!");
	ASSERT((sizeof(Vec2f) == sizeof(c2v)), "Different sizes of vector types!");

	count = minValue(count, C2_MAX_POLYGON_VERTS);
	staticShape.count = int(count);
	memcpy(staticShape.verts, vertices, count * sizeof(Vec2f));
	for (int i = 0; i < count; i++)
	{
		Vec2f vec = (vertices[(i + 1) % count] - vertices[i]);
		vec.normalize();
		staticShape.norms[i] = { vec.y, -vec.x };
	}

	transformShape(transform);
}

const c2Poly& PolygonShape::getDetails() const
{
	return staticShape;
}

void PolygonShape::transformShape(const Transform& newTransform)
{
	aabb = AABB();
	Vec2f pos;
	Matrix rotMatrix = asRotationMatrix(newTransform.rotation);
	for (int i = 0; i < staticShape.count; i++)
	{
		pos = asVec<Vec2f>(staticShape.verts[i]);
		pos = pos * rotMatrix;
		updateAABB(pos);
		scaleVectorByVector(pos, newTransform.scale);
		pos += newTransform.position;
		shape.verts[i] = asVec<c2v>(pos);
		shape.norms[i] = asVec<c2v>(asVec<Vec2f>(staticShape.norms[i]) * rotMatrix);
	}
	shape.count = staticShape.count;

}

void PolygonShape::updateAABB(const Vec2f & newVec)
{
	if (aabb.min.x > newVec.x)
		aabb.min.x = newVec.x;
	else if (aabb.max.x < newVec.x)
		aabb.max.x = newVec.x;

	if (aabb.min.y > newVec.y)
		aabb.min.y = newVec.y;
	else if (aabb.max.y < newVec.y)
		aabb.max.y = newVec.y;
}

ShapeComponent::ShapeComponent()
{
	takeShape<CircleShape>().setRadius(1.f);
}

ShapeBase & ShapeComponent::getShape()
{
	return *shape;
}

const ShapeBase & ShapeComponent::getShape() const
{
	return *shape;
}
