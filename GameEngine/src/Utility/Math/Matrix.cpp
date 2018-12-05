#include "Engine/pch.h"
#include "Engine/Utility/Math/Matrix.h"


const Matrix Matrix::identityMatrix;

Matrix::Matrix()
{
	for (uint8_t i = 0; i < 3; i++)
		for (uint8_t j = 0; j < 3; j++)
			m[i][j] = (i == j);
}

Matrix Matrix::transpose() const
{
	Matrix transpM;

	for (uint8_t i = 0; i < 3; i++)
		for (uint8_t j = 0; j < 3; j++)
			transpM(i, j) = m[j][i];

	return transpM;
}

// operators:


const float_t * Matrix::operator()(uint8_t i) const
{
	ASSERT((i < 3), "Tried to get element out of matrix range");
	if (i < 3)
		return m[i];
	else throw std::out_of_range(std::string("Index out of array's range: "));
}


const float_t& Matrix::operator()(uint8_t i, uint8_t j) const
{
	ASSERT((i < 3 || j < 3), "Tried to get element out of matrix range");
	if (i < 3 && j < 3)
		return m[i][j];
	else throw std::out_of_range(std::string("Index out of array's range: "));
}


float_t * Matrix::operator()(uint8_t i)
{
	ASSERT((i < 3), "Tried to get element out of matrix range");
	if (i < 3)
		return m[i];
	else throw std::out_of_range(std::string("Index out of array's range: "));
}


float_t & Matrix::operator()(uint8_t i, uint8_t j)
{
	ASSERT((i < 3 || j < 3), "Tried to get element out of matrix range");
	if (i < 3 && j < 3)
		return m[i][j];
	else throw std::out_of_range(std::string("Index out of array's range: "));
}


Matrix operator*(const Matrix & left, const Matrix& right)
{
	Matrix product;
	for (uint8_t i = 0; i < 3; i++)
		for (uint8_t j = 0; j < 3; j++)
		{
			product(i, j) = 0;
			for (uint8_t k = 0; k < 3; k++)
				product(i, j) += left(i, k) * right(k, j);
		}
	return product;
}

Vec2f operator*(const Vec2f & left, const Matrix & right)
{
	return Vec2f(	right.m[0][0] * left.x + right.m[1][0] * left.y + right.m[2][0],
					right.m[0][1] * left.x + right.m[1][1] * left.y + right.m[2][1]);
}