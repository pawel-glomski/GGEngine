#pragma once
#include <cmath>
#include <xhash>
#include <ECSpp/Utility/DebugAssert.h>

template<class T>
struct Vec2
{
	template <typename U>
	explicit Vec2(const Vec2<U> & vec);

	Vec2(T x, T y);

	Vec2();


	Vec2<T>& normalize();


	Vec2<T>& clamp(const Vec2<T> minValues, const Vec2<T> maxValues);


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

#include "Vec2.inl"