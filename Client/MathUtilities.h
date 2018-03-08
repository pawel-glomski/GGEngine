#pragma once
#include "Matrix.h"
#include "Vec2.h"
#include "Transformation.h"


template<class T>
T maxValue(const T & value1, const T & value2)
{
	if (value1 > value2)
		return value1;
	return value2;
}

template<class T>
T minValue(const T & value1, const T & value2)
{
	if (value1 < value2)
		return value1;
	return value2;
}

template<class T>
T& clamp(T& value, const T& min, const T& max)
{
	value = minValue(maxValue(value, min), max);
	return value;
}

// returns 1 for values >= 0; resturns -1 for < 0
template<class T>
T sign(const T& signedValue)
{
	if (signedValue >= 0)
		return T(1);
	else
		return T(-1);
}