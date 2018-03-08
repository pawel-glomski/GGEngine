#pragma once
#include "Matrix.h"

#define PI_F 3.14159265358979323846f

class Transformation
{
public:
	Transformation() = default;

	Transformation(const Vect2f & position, float_t rotation);


	void setRotation(float_t newRotation);

	void rotate(float_t rotation);

	void setPosition(const Vect2f & newPosition);

	void moveGlobal(const Vect2f & translation);

	void moveLocal(const Vect2f & translation);

	void moveForward(float_t distance);

	void moveRight(float_t distance);


	Vect2f getPosition() const;

	float_t getRotation() const;


	Vect2f getForwardVector() const;

	Vect2f getRightVector() const;

	
	Matrix getMatrix();
	Matrix getInversedMatrix();

private:
	float_t rotation = 0;
	Matrix rotationM;
	Vect2f position;
};

Matrix asRotationMatrix(float_t rotation);

Matrix asTranslationMatrix(const Vect2f & translation);

Vect2f forwardVectorFromRotation(const Matrix & rotationM);

Vect2f forwardVectorFromRotation(float_t rotation);

Vect2f rightVectorFromRotation(const Matrix & rotationM);

Vect2f rightVectorFromRotation(float_t rotation);

float_t toRadians(float_t degrees);