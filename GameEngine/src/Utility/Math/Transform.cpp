#include "Engine/pch.h"
#include "Engine/Utility/Math/Transform.h"

bool Transform::operator==(const Transform & rhs) const
{
	return (position == rhs.position && rotation == rhs.rotation && scale == rhs.scale);
}

bool Transform::operator!=(const Transform & rhs) const
{
	return !(*this == rhs);
}


Matrix asTranslationMatrix(const Vec2f & translation)
{
	Matrix translationM;
	translationM(2, 0) = translation.x;
	translationM(2, 1) = translation.y;
	return translationM;
}

Matrix asScaleMatrix(const Vec2f & scale)
{
	Matrix scaleM;
	scaleM(0, 0) = scale.x;
	scaleM(1, 1) = scale.y;
	return scaleM;
}

Matrix asRotationMatrix(float_t rotation)
{
	Matrix roll;
	if (rotation)
	{
		roll(0, 0) = cosf(rotation);
		roll(0, 1) = sinf(rotation);
		roll(1, 0) = -sinf(rotation);
		roll(1, 1) = cosf(rotation);
	}
	return roll;
}

Vec2f forwardVectorFromRotation(const Matrix & rotationM)
{
	return Vec2f(rotationM(0, 0), rotationM(0, 1)).normalized();
}

Vec2f forwardVectorFromRotation(float_t rotation)
{
	return forwardVectorFromRotation(asRotationMatrix(rotation));
}

Vec2f rightVectorFromRotation(const Matrix & rotationM)
{
	return Vec2f(rotationM(1, 0), rotationM(1, 1)).normalized();
}

Vec2f rightVectorFromRotation(float_t rotation)
{
	return rightVectorFromRotation(asRotationMatrix(rotation));
}

