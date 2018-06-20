#pragma once
#include "Utilities/Math/MathUtilities.h"
#include "Utilities/Math/Transform.h"

struct HalfSpace
{
	HalfSpace() = default;
	HalfSpace(const Vec2f& pos, const Vec2f& normal) : position(pos), normal(normal) {}
	Vec2f position;
	Vec2f normal;
};

struct Collision
{
	Vec2f normal;
	Vec2f contact_points[2] = {};
	float depth = 0.f;
	size_t count = 0;
};

struct ShapeProjection
{
	ShapeProjection() : left(std::numeric_limits<float>().max()), right(-std::numeric_limits<float>().max()) {}
	float left;
	float right;
};

struct PolygonShape
{
public:
	
	void setVertices(const Vec2f* newVertices, size_t count);

	void setAsBox(const Vec2f& size);


	PolygonShape transformed(const Transform& t) const;

	ShapeProjection projectedOnNormal(const Vec2f& normal) const;

	bool isColliding(const Transform& thisTransform, const PolygonShape& other, const Transform& otherTransform) const;

	Collision collide(const Transform& thisTransform, const PolygonShape& other, const Transform& otherTransform) const;


public:

	static const size_t MaxVerticesCount = 8u;

public:

	size_t vertCount = 0;

	Vec2f vertices[MaxVerticesCount] = {};

	Vec2f normals[MaxVerticesCount] = {};

};


