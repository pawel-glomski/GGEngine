#include "TransformComponent.h"

void TransformComponent::setMobility(Mobility newMobility)
{
	mobility = newMobility;
}
void TransformComponent::setGlobalRotation(float_t newRotation)
{
	if (mobility != Mobility::Movable)
		return;
	if (newRotation >= 2 * PI_F)
		newRotation -= 2 * PI_F;
	else if (newRotation < 0)
		newRotation += 2 * PI_F;

	auto rotationM = asRotationMatrix(newRotation - globalTransform.rotation);
	for (auto & child : attached)
	{
		child->setGlobalPosition(globalTransform.position + (child->getRelativePosition() * rotationM));
		child->setGlobalRotation(newRotation + child->getRelativeRotation());
	}
	globalTransform.rotation = newRotation;
}

void TransformComponent::setRelativeRotation(float_t newRotation)
{
	if(parent)
		setGlobalRotation(parent->globalTransform.rotation + newRotation);
	else
		setGlobalRotation(newRotation);
}

void TransformComponent::rotate(float_t deltaRotation)
{
	setGlobalRotation(globalTransform.rotation + deltaRotation);
}

void TransformComponent::setGlobalPosition(const Vec2f & newPosition)
{
	if (mobility != Mobility::Movable)
		return;
	for (auto & child : attached)
		child->setGlobalPosition(newPosition + child->getRelativePosition());
	globalTransform.position = newPosition;
}

void TransformComponent::setRelativePosition(const Vec2f & newPosition)
{
	if(parent)
		setGlobalPosition(parent->globalTransform.position + newPosition);
	else
		setGlobalPosition(newPosition);
}

void TransformComponent::moveGlobal(const Vec2f & translation)
{
	setGlobalPosition(globalTransform.position + translation);
}

void TransformComponent::moveLocal(const Vec2f & translation)
{
	moveGlobal(translation * asRotationMatrix(getGlobalRotation()));
}

void TransformComponent::moveForward(float_t distance)
{
	moveLocal({ distance, 0 });
}

void TransformComponent::moveRight(float_t distance)
{
	moveLocal({ 0, distance });
}

void TransformComponent::setRelativeTransform(const Transform & transform)
{
	setRelativePosition(transform.position);
	setRelativeRotation(transform.rotation);
	setRelativeScale(transform.scaleV);
}

void TransformComponent::setGlobalTransform(const Transform & transform)
{
	setGlobalPosition(transform.position);
	setGlobalRotation(transform.rotation);
	setGlobalScale(transform.scaleV);
}

void TransformComponent::setGlobalScale(const Vec2f & newScale)
{
	if (mobility != Mobility::Movable)
		return;
	for (auto & child : attached)
		child->setGlobalScale(VectorScaledByVector(newScale, child->getRelativeScale()));
	globalTransform.scaleV = newScale;
}

void TransformComponent::setRelativeScale(const Vec2f & newScale)
{
	if(parent)
		setGlobalScale(VectorScaledByVector(parent->globalTransform.scaleV, newScale));
	else
		setGlobalScale(newScale);
}

void TransformComponent::scale(const Vec2f & scaleV)
{
	setGlobalScale(VectorScaledByVector(globalTransform.scaleV, scaleV));
}

TransformComponent::Mobility TransformComponent::getMobility() const
{
	return mobility;
}

Vec2f TransformComponent::getGlobalPosition() const
{
	return globalTransform.position;
}

Vec2f TransformComponent::getRelativePosition() const
{
	if (parent)
		return globalTransform.position - parent->globalTransform.position;
	return globalTransform.position;
}

float_t TransformComponent::getGlobalRotation() const
{
	return globalTransform.rotation;
}

float_t TransformComponent::getRelativeRotation() const
{
	if (parent)
		return globalTransform.rotation - parent->globalTransform.rotation;
	return globalTransform.rotation;
}

Vec2f TransformComponent::getGlobalScale() const
{
	return globalTransform.scaleV;
}

Vec2f TransformComponent::getRelativeScale() const
{
	if (parent)
		return VectorScaledByVector(globalTransform.scaleV, 1.f / parent->globalTransform.scaleV);
	return globalTransform.scaleV;
}

Vec2f TransformComponent::getForwardVector() const
{
	return forwardVectorFromRotation(globalTransform.rotation);
}

Vec2f TransformComponent::getRightVector() const
{
	return rightVectorFromRotation(globalTransform.rotation);
}

Transform TransformComponent::getRelativeTransform() const
{
	return Transform(getRelativePosition(), getRelativeRotation(), getRelativeScale());
}

const Transform& TransformComponent::getGlobalTransform() const
{
	return globalTransform;
}