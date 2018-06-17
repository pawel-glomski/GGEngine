#pragma once
#include "Utilities/Math/MathUtilities.h"

struct HalfSpace
{
	Vec2f normal;
	float distance = 0.f;
};


struct Collision
{
	Vec2f n;
	Vec2f contact_points[2] = {};
	float depths[2] = {};
	size_t count = 0;
};


struct PointProjection
{
	size_t index = 0;
	float magnitude = 0.f;
};

struct ShapeProjection
{
	PointProjection left;
	PointProjection right;
};


struct Polygon
{
public:
	
	void setVertices(const Vec2f* newVertices, size_t count);


	ShapeProjection projectedOnNormal(const Vec2f& normal) const;

	Collision collide(const Polygon& other) const;

public:

	static const size_t MaxVerticesCount = 8u;

public:

	size_t count = 0;

	Vec2f vertices[MaxVerticesCount] = {};

	Vec2f normals[MaxVerticesCount] = {};

};

