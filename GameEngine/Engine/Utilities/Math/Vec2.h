#pragma once
#include <cstdint>
#include <iostream>
#include <ECSpp/Utility/DebugAssert.h>
#include <algorithm>

template<class T>
struct Vec2
{
	template <typename U>
	explicit Vec2(const Vec2<U> & vec);

	Vec2(T x, T y);

	Vec2();


	Vec2<T>& normalize();


	Vec2<T>& clamp(const Vec2<T> minValues, const Vec2<T> maxValues);

	Vec2<T>& clamp(float length);


	T length() const;

	Vec2<T>	normalized() const;

public:

	T x;

	T y;

	static const Vec2<T> ZeroVector;

	static const Vec2<T> OneVector;
};

template<class T>
const Vec2<T> Vec2<T>::ZeroVector = Vec2<T>(0, 0);
template<class T>
const Vec2<T> Vec2<T>::OneVector = Vec2<T>(1, 1);


typedef Vec2<size_t>	Vec2u;

typedef Vec2<ptrdiff_t>	Vec2i;

typedef Vec2<float_t>	Vec2f;

typedef Vec2<double_t>	Vec2d;

// utilities

template<class T>
float_t	dotProduct(const Vec2<T> & vec1, const Vec2<T> & vec2);

template<class T>
float_t crossProduct(const Vec2<T> & vec1, const Vec2<T> & vec2);

template<class T>
float_t	angleBetweenVectors(Vec2<T> vec1, Vec2<T> vec2);

template<class T>
inline T& clamp(T& value, const T& min, const T& max)
{
	value = clamped(value, min, max);
	return value;
}

template<class T>
inline T clamped(const T & value, const T& min, const T& max)
{
	return minValue(maxValue(value, min), max);
}

inline size_t hash_combine(size_t lhs, size_t rhs) 
{
	lhs ^= rhs + 0xc6a4a7935bd1e995ull + (lhs << 6) + (lhs >> 2);
	return lhs;
}

namespace std
{
	template<class T>
	struct hash<Vec2<T>>
	{
		size_t operator()(const Vec2<T>& vec)
		{
			return hash_combine(hasher(vec.x), hasher(vec.y));
		}
		std::hash<T> hasher;
	};
}

#include "Vec2.inl"