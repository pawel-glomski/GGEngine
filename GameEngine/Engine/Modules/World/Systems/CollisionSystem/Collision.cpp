#include "Collision.h"
#include <ECSpp/Utility/DebugAssert.h>

struct PenetrationData
{
	static const float NonCollidingDepth;

	float depth = NonCollidingDepth;
	size_t vertIdxA = 0;
	size_t vertIdxB = 0;
	Vec2f normal;
};

const float PenetrationData::NonCollidingDepth = std::numeric_limits<float>().max();

void PolygonShape::setAsBox(const Vec2f& size)
{
	Vec2f vertices[4];
	Vec2f halfSize(size * 0.5f);
	vertices[0] = -halfSize;
	vertices[1] = { halfSize.x, -halfSize.y };
	vertices[2] = halfSize;
	vertices[3] = { -halfSize.x, halfSize.y };
	setVertices(vertices, 4);
}


void PolygonShape::setVertices(const Vec2f * newVertices, size_t inputCount)
{
	ASSERT((inputCount && inputCount >= 3 && inputCount <= MaxVerticesCount), "Wrong vertices count");
	if (!inputCount || inputCount < 3)
		return;

	vertCount = minValue(inputCount, MaxVerticesCount);
	memcpy(vertices, newVertices, vertCount * sizeof(Vec2f));
	for (int i = 0; i < vertCount; i++)
	{
		Vec2f vec = (vertices[(i + 1) % vertCount] - vertices[i]);
		vec.normalize();
		normals[i] = { vec.y, -vec.x };
	}
}

PolygonShape PolygonShape::transformed(const Transform& t) const
{
	PolygonShape result = *this;
	Matrix rMat = asRotationMatrix(t.rotation);
	for (size_t i = 0; i < vertCount; ++i)
	{
		result.normals[i] = result.normals[i] * rMat;
		result.vertices[i] = result.vertices[i] * rMat;
		scaleVectorByVector(result.vertices[i], t.scale);
		result.vertices[i] += t.position;
	}
	return result;
}

ShapeProjection PolygonShape::projectedOnNormal(const Vec2f& normal) const
{
	ShapeProjection result;
	for (size_t i = 0; i < vertCount; ++i)
	{
		float projMagnitude = dotProduct(normal, vertices[i]);
		if (result.left.magnitude >= projMagnitude)
		{
			result.left.magnitude = projMagnitude;
			if(i > result.left.index)
				result.left.index = i;
		}
		if (result.right.magnitude <= projMagnitude)
		{
			result.right.magnitude = projMagnitude;
			if (i > result.left.index)
				result.left.index = i;
		}
	}
	return result;
}

static PenetrationData computeMinPenUsingShapeA(const PolygonShape& shapeA, const PolygonShape& shapeB)
{
	PenetrationData result;
	for (size_t i = 0; i < shapeA.vertCount; ++i)
	{
		ShapeProjection proj[2] = { shapeA.projectedOnNormal(shapeA.normals[i]), shapeB.projectedOnNormal(shapeA.normals[i]) };
		uint8_t rightMostProjIdx = proj[0].right.magnitude > proj[1].right.magnitude ? 0 : 1;

		float penDepth = proj[!rightMostProjIdx].right.magnitude - proj[rightMostProjIdx].left.magnitude;
		if (penDepth < 0)
			return PenetrationData();

		if (result.depth > penDepth)
		{
			result.depth = penDepth;
			if (rightMostProjIdx == 0)
			{
				result.vertIdxA = proj[0].left.index;
				result.vertIdxB = proj[1].right.index;
			}
			else
			{
				result.vertIdxA = proj[0].right.index;
				result.vertIdxB = proj[1].left.index;
			}
			result.normal = shapeA.normals[i];
		}
	}
	return result;
}



bool PolygonShape::isColliding(const Transform & thisTransform, const PolygonShape & other, const Transform & otherTransform) const
{
	return(computeMinPenUsingShapeA(this->transformed(thisTransform), other.transformed(otherTransform)).depth != PenetrationData::NonCollidingDepth &&
		computeMinPenUsingShapeA(other.transformed(otherTransform), this->transformed(thisTransform)).depth != PenetrationData::NonCollidingDepth);
}

Vec2f computeContactPoint(const Vec2f& vertA1, const Vec2f& vertA2, const Vec2f& vertB1, const Vec2f& vertB2)
{
	Vec2f A12 = (vertA2 - vertA1);
	Vec2f B12 = (vertB2 - vertB1);
	float dirCross = crossProduct(A12, B12);
	if (dirCross)
	{
		float t = crossProduct((vertB1 - vertA1), B12) / dirCross;
		float u = crossProduct((vertB1 - vertA1), A12) / dirCross; 

		//if (u < 0 || u > 1)
			return vertB1 + B12 * clamp(u, 0.f, 1.f);
		//return vertA1 + A12 * clamp(t, 0.f, 1.f);
	}
	B12.normalize();
	return dotProduct(vertA2, B12) * B12;
}


Collision PolygonShape::collide(const Transform & thisTransform, const PolygonShape & other, const Transform & otherTransform) const
{
	Collision result;
	PolygonShape shapeA = this->transformed(thisTransform);
	PolygonShape shapeB = other.transformed(otherTransform);

	PenetrationData minPenA = computeMinPenUsingShapeA(shapeA, shapeB);
	PenetrationData minPenB = computeMinPenUsingShapeA(shapeB, shapeA);

	if (minPenA.depth < minPenB.depth)
	{
		result.normal = minPenA.normal;
		result.depth = minPenA.depth;
		std::cout << "here";
		result.contact_points[0] = computeContactPoint(	shapeA.vertices[minPenB.vertIdxA], shapeA.vertices[(minPenB.vertIdxA + 1) % shapeA.vertCount], 
														shapeB.vertices[minPenB.vertIdxB], shapeB.vertices[(minPenB.vertIdxB + 1) % shapeB.vertCount]);

		result.contact_points[0] = computeContactPoint(	shapeA.vertices[minPenB.vertIdxA], shapeA.vertices[(minPenB.vertIdxA + 1) % shapeA.vertCount], 
														shapeB.vertices[minPenB.vertIdxB], shapeB.vertices[(minPenB.vertIdxB + shapeB.vertCount - 1) % shapeB.vertCount]);
	}
	else
	{
		size_t holder = minPenB.vertIdxA;
		minPenB.vertIdxA = minPenB.vertIdxB;
		minPenB.vertIdxB = holder;
		result.normal = -minPenB.normal;
		result.depth = minPenB.depth;


		std::cout << minPenB.vertIdxB << " " << (minPenB.vertIdxB + 1) % shapeB.vertCount << std::endl;

		result.contact_points[0] = computeContactPoint(	shapeB.vertices[minPenB.vertIdxB], shapeB.vertices[(minPenB.vertIdxB + 1) % shapeB.vertCount],
														shapeA.vertices[minPenB.vertIdxA], shapeA.vertices[(minPenB.vertIdxA + 1) % shapeA.vertCount]);

		result.contact_points[1] = computeContactPoint(	shapeB.vertices[minPenB.vertIdxB], shapeB.vertices[(minPenB.vertIdxB + 1) % shapeB.vertCount],
														shapeA.vertices[minPenB.vertIdxA], shapeA.vertices[(minPenB.vertIdxA + shapeA.vertCount - 1) % shapeA.vertCount]);
	}

	result.count = 2;
	return result;
}