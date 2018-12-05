#pragma once
#include "Vec2.h"

// using left-hand coordinate system with forward as X and right as Y
struct Matrix 
{		
	Matrix();
	Matrix transpose() const;


	const float_t*	operator()(uint8_t i) const;
	const float_t&	operator()(uint8_t i, uint8_t j) const;
	float_t*		operator()(uint8_t i);
	float_t&		operator()(uint8_t i, uint8_t j);




	float_t m[3][3];

	static const Matrix identityMatrix;
};

Matrix operator*(const Matrix & left, const Matrix& right);

Vec2f operator*(const Vec2f & left, const Matrix & right);
std::ostream& operator<<(std::ostream& os, const Matrix & m);