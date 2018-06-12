#include "ShapeComponent.h"
#include "DisplayModule.h"

#define TINYC2_IMPLEMENTATION
#include "tinyc2.h"

ShapeBase::ShapeBase(c2Shape & shape) : shapeRef(shape)
{
}

c2Manifold ShapeBase::collisionManifold(const ShapeBase & otherShape) const
{
	c2Manifold manifold;
	c2x thisC2transform = c2Transform(asVec<c2v>(transform.position), transform.rotation);
	c2x otherC2transform = c2Transform(asVec<c2v>(otherShape.transform.position), otherShape.transform.rotation);

	c2Collide(&shapeRef, &thisC2transform, shapeRef.type, &otherShape.shapeRef, &otherC2transform, otherShape.shapeRef.type, &manifold);

	return manifold;
}

bool ShapeBase::isColliding(const ShapeBase & otherShape) const
{
	c2x thisC2transform = c2Transform(asVec<c2v>(transform.position), transform.rotation);
	c2x otherC2transform = c2Transform(asVec<c2v>(otherShape.transform.position), otherShape.transform.rotation);

	return c2Collided(&shapeRef, &thisC2transform, shapeRef.type, &otherShape.shapeRef, &otherC2transform, otherShape.shapeRef.type);
}

void ShapeBase::setTransform(Transform newTransform)
{
	if (transform != newTransform)
	{
		if (shapeRef.type == C2_TYPE::C2_CIRCLE)
		{
			if (newTransform.scaleV.x != newTransform.scaleV.y)
			{
				ASSERT((newTransform.scaleV.x == newTransform.scaleV.y), "Circle cannot be scaled differently in both dimentions. It is scaled now only by value of x dimension scale");
				newTransform.scaleV = Vec2f(newTransform.scaleV.x, newTransform.scaleV.x);
			}
			static_cast<c2Circle&>(shapeRef).p =  asVec<c2v>(newTransform.position);
		}
		if (transform.scaleV != newTransform.scaleV)
		{
			Vec2f scale = VectorScaledByVector(newTransform.scaleV, 1.f / transform.scaleV);
			scaleShape(scale);
		}
		transform = newTransform;
	}
}

const Transform & ShapeBase::getTransform() const
{
	return transform;
}

C2_TYPE ShapeBase::getType() const
{
	return shapeRef.type;
}




CircleShape::CircleShape() : ShapeBase(shape)
{
}

void CircleShape::setRadius(float_t newRadius)
{
	shape.r = newRadius;
}

const c2Circle & CircleShape::getDetails() const
{
	return shape;
}

void CircleShape::scaleShape(const Vec2f & scaleV)
{
	shape.r *= scaleV.x;
}



PolygonShape::PolygonShape() : ShapeBase(shape)
{
}

void PolygonShape::setAsBox(const Vec2f & size)
{
	Vec2f vertices[4];

	Vec2f halfSize(size / 2.f);

	vertices[0] = -halfSize;
	vertices[1] = { halfSize.x, -halfSize.y };
	vertices[2] = halfSize;
	vertices[3] = { -halfSize.x, halfSize.y };


	setVertices(vertices, 4);
}

void PolygonShape::setVertices(const Vec2f* vertices, int count)
{
	ASSERT((count <= C2_MAX_POLYGON_VERTS), "Vertices count cannot be greater b2_maxPolygonVertices!");
	ASSERT((sizeof(Vec2f) == sizeof(c2v)), "Different sizes of vector types!");

	count = minValue(count, C2_MAX_POLYGON_VERTS);

	shape.count = int(count);
	memcpy(shape.verts, vertices, count * sizeof(Vec2f));
	for (int i = 0; i < count; i++)
	{
		Vec2f vec = (vertices[(i + 1) % count] - vertices[i]);
		vec.normalize();
		shape.norms[i] = c2v(vec.y, -vec.x);
	}

	// that should always be at (0, 0)
	//shape.m_centroid = ComputeCentroid(shape.m_vertices, int32(count));
}

const c2Poly& PolygonShape::getDetails() const
{
	return shape;
}

void PolygonShape::scaleShape(const Vec2f & scaleV)
{
	for (int i = 0; i < shape.count; i++)
	{
		shape.verts[i].x *= scaleV.x;
		shape.verts[i].y *= scaleV.y;
	}
}




ShapeComponent::ShapeComponent()
{
	takeShape<CircleShape>().setRadius(0.5f);
}

ShapeBase & ShapeComponent::getShape()
{
	return *shape;
}

const ShapeBase & ShapeComponent::getShape() const
{
	return *shape;
}
