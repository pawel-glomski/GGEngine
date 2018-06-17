#include "Collision.h"



void Polygon::setVertices(const Vec2f * newVertices, size_t inputCount)
{
	if (!count)
		return;

	count = minValue(inputCount, MaxVerticesCount);
	memcpy(vertices, newVertices, count * sizeof(Vec2f));
	for (int i = 0; i < count; i++)
	{
		Vec2f vec = (vertices[(i + 1) % count] - vertices[i]);
		vec.normalize();
		normals[i] = { vec.y, -vec.x };
	}
}

ShapeProjection Polygon::projectedOnNormal(const Vec2f& normal) const
{
	float leftVal = 0.f, rightVal = 0.f;
	size_t leftIdx = 0, rightIdx = 0;

	for (size_t i = 0; i < count; ++i)
	{
		float projMagnitude = dotProduct(normal, vertices[i]);
		if (leftVal > projMagnitude)
		{
			leftVal = projMagnitude;
			leftIdx = i;
		}
		else if (rightVal > projMagnitude)
		{
			rightVal = projMagnitude;
			rightIdx = i;
		}
	}
	return { leftIdx, rightIdx };
}

Collision Polygon::collide(const Polygon & other) const
{
	
}
