#pragma once
#include <cstdint>
#include "Matrix.h"
#include "Vec2.h"


#define PI_F 3.14159265358979323846f

template<class T>
inline T maxValue(const T & value1, const T & value2)
{
	if (value1 > value2)
		return value1;
	return value2;
}

template<class T>
inline T minValue(const T & value1, const T & value2)
{
	if (value1 < value2)
		return value1;
	return value2;
}

// returns 1 for value > 0; 0 for value == 0, -1 for value < 0
template<class T>
inline int sign(const T& value)
{
	if (!value)		return 0;
	if (value > 0)	return 1;
	return -1;
}

template<class T>
inline Vec2i signs(const Vec2<T>& vec)
{
	return Vec2i(sign(vec.x), sign(vec.y));
}

inline float_t toRadians(float_t degrees)
{
	return PI_F / 180.f * degrees;
}

inline float_t toDegrees(float_t radians)
{
	return 180.f * radians / PI_F ;
}

template<class T>
inline Vec2<T>& scaleVectorByVector(Vec2<T>& scaled, const Vec2<T> & scale)
{
	scaled.x *= scale.x;
	scaled.y *= scale.y;
	return scaled;
}

template<class T>
inline Vec2<T> VectorScaledByVector(Vec2<T> scaled, const Vec2<T> & scale)
{
	return scaleVectorByVector(scaled, scale);
}

template<class T, class U>
inline T asVec(const U& vec)
{
	using ComponentType = decltype(T::x);

	return T(ComponentType(vec.x), ComponentType(vec.y));
}