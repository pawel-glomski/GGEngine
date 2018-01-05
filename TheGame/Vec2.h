#pragma once
#include <cstdint>
#include <iostream>

template<class T>
struct Vect2
{
	template <typename U>
	explicit Vect2(const Vect2<U> & vec);
	Vect2(T x, T y);
	Vect2();

	T			length() const;
	Vect2<T>		normalized() const;
	Vect2<T>&	normalize();

	T x;
	T y;

	static const Vect2<T> zeroVector;
	static const Vect2<T> oneVector;
};

template<class T>
const Vect2<T> Vect2<T>::zeroVector = Vect2<T>(0, 0);
template<class T>
const Vect2<T> Vect2<T>::oneVector = Vect2<T>(1, 1);

typedef Vect2<uint32_t> Vect2u;
typedef Vect2<int32_t>	Vect2i;
typedef Vect2<float_t>	Vect2f;
typedef Vect2<double_t> Vect2d;

#include "Vec2.inl"