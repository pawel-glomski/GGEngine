#include "Collision.h"
#include <ECSpp/Utility/DebugAssert.h>

struct PenetrationData
{
	enum ShapeIdx {A, B};

	static const float NonCollidingDepth;

	float depth = NonCollidingDepth;
	ShapeIdx shapeIdx = ShapeIdx::A;
	size_t normalIdx = 0;;
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
	result.left = dotProduct(normal, vertices[0]);
	result.right = result.left;

	for (size_t i = 1; i < vertCount; ++i)
		if (float projMagnitude = dotProduct(normal, vertices[i]); result.left > projMagnitude)
			result.left = projMagnitude;
		else if (result.right < projMagnitude)
			result.right = projMagnitude;
	return result;
}

static PenetrationData computePenetrationOnShapeA(const PolygonShape& shapeA, const PolygonShape& shapeB)
{
	PenetrationData result;
	for (size_t i = 0; i < shapeA.vertCount; ++i)
	{
		ShapeProjection proj[2] = { shapeA.projectedOnNormal(shapeA.normals[i]), shapeB.projectedOnNormal(shapeA.normals[i]) };
		uint8_t rightMostProjIdx = proj[0].right > proj[1].right ? 0 : 1;
		float depth = proj[!rightMostProjIdx].right - proj[rightMostProjIdx].left;
		if (depth < 0)
			return PenetrationData();

		if (result.depth == depth && rightMostProjIdx != 0)
			result.normalIdx = i;
		else if (result.depth > depth)
		{
			result.depth = depth;
			result.normalIdx = i;
		}
	}

	return result;
}

static PenetrationData computePenetration(const PolygonShape& shapeA, const PolygonShape& shapeB)
{
	PenetrationData peneA = computePenetrationOnShapeA(shapeA, shapeB);
	if (peneA.depth != PenetrationData::NonCollidingDepth)
	{
		PenetrationData peneB = computePenetrationOnShapeA(shapeB, shapeA);
		if (peneB.depth == PenetrationData::NonCollidingDepth)
			return PenetrationData();

		if (peneA.depth > peneB.depth)
		{
			peneB.shapeIdx = PenetrationData::ShapeIdx::B;
			return peneB;
		}
	}
	return peneA;
}

bool PolygonShape::isColliding(const Transform & thisTransform, const PolygonShape & other, const Transform & otherTransform) const
{
	return(computePenetration(this->transformed(thisTransform), other.transformed(otherTransform)).depth != PenetrationData::NonCollidingDepth);
}

std::pair<bool, Vec2f> edgesCommonPoint(const Vec2f& vertA1, const Vec2f& vertA2, const Vec2f& vertB1, const Vec2f& vertB2)
{
	Vec2f A12 = (vertA2 - vertA1);
	Vec2f B12 = (vertB2 - vertB1);
	float dirCross = crossProduct(A12, B12);
	if (dirCross)
	{
		float t = crossProduct((vertB1 - vertA1), B12) / dirCross;
		float u = crossProduct((vertB1 - vertA1), A12) / dirCross;
		if (t >= 0 && t <= 1 && u >= 0 && u <= 1)
			return { true, vertA1 + A12 * t };
	}
	return { false, Vec2f::ZeroVector };
}


Collision PolygonShape::collide(const Transform & thisTransform, const PolygonShape & other, const Transform & otherTransform) const
{
	PolygonShape shape[2] = { this->transformed(thisTransform) , other.transformed(otherTransform) };
	PenetrationData pene = computePenetration(shape[0], shape[1]);
	Collision result;
	if (pene.depth != PenetrationData::NonCollidingDepth)
	{
		PolygonShape& contactShape = shape[pene.shapeIdx];
		PolygonShape& otherShape = shape[!pene.shapeIdx];
		result.count = 2;
		result.depth = pene.depth;
		result.normal = contactShape.normals[pene.normalIdx];
		result.contact_points[0] = contactShape.vertices[pene.normalIdx];
		result.contact_points[1] = contactShape.vertices[(pene.normalIdx + 1) % contactShape.vertCount];

		for (size_t i = 0; i < otherShape.vertCount; ++i)
		{
			auto point = edgesCommonPoint(result.contact_points[0], result.contact_points[1], otherShape.vertices[i], otherShape.vertices[(i + 1) % otherShape.vertCount]);
			if (point.first)
			{
				Vec2f commonToClipPoint = result.contact_points[0] - point.second;
				if (dotProduct(commonToClipPoint, otherShape.normals[i]) > 0)
				{
					result.contact_points[0] = point.second;
					continue;
				}
				commonToClipPoint = result.contact_points[1] - point.second;
				if (dotProduct(commonToClipPoint, otherShape.normals[i]) > 0)
					result.contact_points[1] = point.second;
			}
		}
	}
	return result;
}