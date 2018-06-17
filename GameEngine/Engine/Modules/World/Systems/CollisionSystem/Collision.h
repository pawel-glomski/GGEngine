#pragma once
#include "Utilities/Math/MathUtilities.h"

struct HalfSpace
{
	Vec2f normal;
	float distance = 0.f;
};


class Polygon
{
public:


public:
	
	void setVertices(const Vec2f* newVertices, size_t count);

public:

	static const size_t MaxVerticesCount = 8u;

private:

	size_t count = 0;

	Vec2f vertices[MaxVerticesCount] = {};

	Vec2f normals[MaxVerticesCount] = {};

};

struct Collision
{
	Vec2f n;
	Vec2f contact_points[2] = {};
	float depths[2] = {};
	size_t count = 0;
};