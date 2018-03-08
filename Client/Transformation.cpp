#include "Transformation.h"

Transformation::Transformation(const Vect2f & position, float_t rotation) : position(position), rotation(rotation), rotationM(asRotationMatrix(rotation))
{
}

void Transformation::setRotation(float_t newRotation)
{
	if (newRotation >= 2 * PI_F)
		newRotation -= 2 * PI_F;
	else if (newRotation < 0)
		newRotation += 2 * PI_F;

	rotation = newRotation;
	rotationM = asRotationMatrix(newRotation);
}

void Transformation::rotate(float_t deltaRotation)
{
	setRotation(rotation + deltaRotation);
}

void Transformation::setPosition(const Vect2f & newPosition)
{
	position = newPosition;
}

void Transformation::moveGlobal(const Vect2f & translation)
{
	position += translation;
}

void Transformation::moveLocal(const Vect2f & translation)
{
	position += (translation * rotationM);
}

void Transformation::moveForward(float_t distance)
{
	moveLocal({ distance, 0 });
}

void Transformation::moveRight(float_t distance)
{
	moveLocal({ 0, distance });
}

Vect2f Transformation::getPosition() const
{
	return position;
}

float_t Transformation::getRotation() const
{
	return rotation;
}

Vect2f Transformation::getForwardVector() const
{
	return forwardVectorFromRotation(rotationM);
}

Vect2f Transformation::getRightVector() const
{
	return rightVectorFromRotation(rotationM);
}
Matrix Transformation::getMatrix()
{
	return rotationM * asTranslationMatrix(position);
}
Matrix Transformation::getInversedMatrix()
{
	return asRotationMatrix(-rotation) * asTranslationMatrix(-position);
}
// utilities:

Matrix asTranslationMatrix(const Vect2f & translation)
{
	Matrix translationM;
	translationM(2, 0) = translation.x;
	translationM(2, 1) = translation.y;
	return translationM;
}

Matrix asRotationMatrix(float_t rotation)
{
	Matrix roll;
	if (rotation)
	{
		roll(0, 0) = cos(rotation);
		roll(0, 1) = sin(rotation);
		roll(1, 0) = -sin(rotation);
		roll(1, 1) = cos(rotation);
	}
	return roll;
}

Vect2f forwardVectorFromRotation(const Matrix & rotationM)
{
	return Vect2f(rotationM(0, 0), rotationM(0, 1)).normalized();
}

Vect2f forwardVectorFromRotation(float_t rotation)
{
	return forwardVectorFromRotation(asRotationMatrix(rotation));
}

Vect2f rightVectorFromRotation(const Matrix & rotationM)
{
	return Vect2f(rotationM(1, 0), rotationM(1, 1)).normalized();
}

Vect2f rightVectorFromRotation(float_t rotation)
{
	return rightVectorFromRotation(asRotationMatrix(rotation));
}

float_t toRadians(float_t degrees)
{
	return PI_F / 180.f * degrees;
}
