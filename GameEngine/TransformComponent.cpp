#include "TransformComponent.h"


void TransformComponent::setMobility(Mobility newMobility)
{
	mobility = newMobility;
}

void TransformComponent::setRotation(float_t newRotation)
{
	if (newRotation >= 2 * PI_F)
		newRotation -= 2 * PI_F;
	else if (newRotation < 0)
		newRotation += 2 * PI_F;

	globalTransform.rotation = newRotation;
}

void TransformComponent::rotate(float_t deltaRotation)
{
	setRotation(globalTransform.rotation + deltaRotation);
}


void TransformComponent::setScale(const Vec2f & newScale)
{
	globalTransform.scale = newScale;
}

void TransformComponent::scale(const Vec2f & scale)
{
	setScale(VectorScaledByVector(globalTransform.scale, scale));
}


void TransformComponent::setPosition(const Vec2f & newPosition)
{
	globalTransform.position = newPosition;
}

void TransformComponent::moveGlobal(const Vec2f & translation)
{
	setPosition(globalTransform.position + translation);
}

void TransformComponent::moveLocal(const Vec2f & translation)
{
	moveGlobal(translation * asRotationMatrix(getRotation()));
}

void TransformComponent::moveForward(float_t distance)
{
	moveLocal({ distance, 0 });
}

void TransformComponent::moveRight(float_t distance)
{
	moveLocal({ 0, distance });
}

void TransformComponent::setTransform(const Transform & transform)
{
	setPosition(transform.position);
	setRotation(transform.rotation);
	setScale(transform.scale);
}



TransformComponent::Mobility TransformComponent::getMobility() const
{
	return mobility;
}

const Vec2f& TransformComponent::getPosition() const
{
	return globalTransform.position;
}

float_t TransformComponent::getRotation() const
{
	return globalTransform.rotation;
}

const Vec2f& TransformComponent::getScale() const
{
	return globalTransform.scale;
}

Vec2f TransformComponent::getForwardVector() const
{
	return forwardVectorFromRotation(globalTransform.rotation);
}

Vec2f TransformComponent::getRightVector() const
{
	return rightVectorFromRotation(globalTransform.rotation);
}

const Transform& TransformComponent::getTransform() const
{
	return globalTransform;
}