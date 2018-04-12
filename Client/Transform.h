#pragma once
#include "MathUtilities.h"

struct Transform
{
	Vec2f position;

	float_t rotation = 0.f;

	Vec2f scaleV = Vec2f::oneVector;


	Transform() = default;

	Transform(Vec2f position, float_t rotation, Vec2f scaleV) : position(position), rotation(rotation), scaleV(scaleV) {}
};

Matrix asRotationMatrix(float_t rotation);

Matrix asTranslationMatrix(const Vec2f & translation);

Matrix asScaleMatrix(const Vec2f & scale);

Vec2f forwardVectorFromRotation(const Matrix & rotationM);

Vec2f forwardVectorFromRotation(float_t rotation);

Vec2f rightVectorFromRotation(const Matrix & rotationM);

Vec2f rightVectorFromRotation(float_t rotation);