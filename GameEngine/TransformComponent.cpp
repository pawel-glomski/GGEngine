#include "TransformComponent.h"


void TransformComponent::setMobility(Mobility newMobility)
{
	mobility = newMobility;
}

void TransformComponent::setGlobalRotation(float_t newRotation)
{
	if (newRotation == globalTransform.rotation)
		return;

	if (mobility == Mobility::RelativeStatic)
		if (parent)
			return parent->rotate(newRotation - globalTransform.rotation);

	setGlobalRotationUniversal(newRotation);
}

void TransformComponent::setGlobalRotationUniversal(float_t newRotation)
{
	if (mobility == Mobility::WorldStatic)
		return;

	if (newRotation >= 2 * PI_F)
		newRotation -= 2 * PI_F;
	else if (newRotation < 0)
		newRotation += 2 * PI_F;

	auto rotationM = asRotationMatrix(newRotation - globalTransform.rotation);
	for (auto & child : attached)
	{
		child->setGlobalPositionUniversal(globalTransform.position + (child->getRelativePosition() * rotationM));
		child->setGlobalRotationUniversal(newRotation + child->getRelativeRotation());
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



void TransformComponent::setGlobalScale(const Vec2f & newScale)
{
	if (newScale == globalTransform.scaleV)
		return;

	if (mobility == Mobility::RelativeStatic)
		if (parent)
			return parent->scale(VectorScaledByVector(newScale, 1.f / globalTransform.scaleV));

	setGlobalScaleUniversal(newScale);
}

void TransformComponent::setGlobalScaleUniversal(const Vec2f & newScale)
{
	if (mobility == Mobility::WorldStatic)
		return;

	for (auto & child : attached)
		child->setGlobalScaleUniversal(VectorScaledByVector(newScale, child->getRelativeScale()));
	globalTransform.scaleV = newScale;
}

void TransformComponent::setRelativeScale(const Vec2f & newScale)
{
	if (parent)
		return setGlobalScale(VectorScaledByVector(parent->globalTransform.scaleV, newScale));
	setGlobalScale(newScale);
}

void TransformComponent::scale(const Vec2f & scaleV)
{
	setGlobalScale(VectorScaledByVector(globalTransform.scaleV, scaleV));
}



void TransformComponent::setGlobalPosition(const Vec2f & newPosition)
{
	if (newPosition == globalTransform.position)
		return;

	if (mobility == Mobility::RelativeStatic)
		if (parent)
			return parent->moveGlobal(newPosition - globalTransform.position);
	setGlobalPositionUniversal(newPosition);
}

void TransformComponent::setGlobalPositionUniversal(const Vec2f & newPosition)
{
	if (mobility == Mobility::WorldStatic)
		return;

	for (auto & child : attached)
		child->setGlobalPositionUniversal(newPosition + child->getRelativePosition());
	globalTransform.position = newPosition;
}

void TransformComponent::setRelativePosition(const Vec2f & newPosition)
{
	if(parent)
		setGlobalPosition(parent->globalTransform.position + newPosition);
	else
		setGlobalPosition(newPosition);
}

void TransformComponent::setParentLocalPosition(const Vec2f & newPosition)
{
	if (parent)
		return setGlobalPosition(parent->globalTransform.position + newPosition * asRotationMatrix(parent->globalTransform.rotation));
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

void TransformComponent::moveParentLocal(const Vec2f & translation)
{
	if (parent)
		return moveGlobal(translation * asRotationMatrix(parent->globalTransform.rotation));
	moveGlobal(translation);
}

void TransformComponent::moveForward(float_t distance)
{
	moveLocal({ distance, 0 });
}

void TransformComponent::moveRight(float_t distance)
{
	moveLocal({ 0, distance });
}



void TransformComponent::setGlobalTransform(const Transform & transform)
{
	setGlobalPosition(transform.position);
	setGlobalRotation(transform.rotation);
	setGlobalScale(transform.scaleV);
}

void TransformComponent::setRelativeTransform(const Transform & transform)
{
	setRelativePosition(transform.position);
	setRelativeRotation(transform.rotation);
	setRelativeScale(transform.scaleV);
}

void TransformComponent::setParentLocalTransform(const Transform & transform)
{
	setParentLocalPosition(transform.position);
	setRelativeRotation(transform.rotation);
	setRelativeScale(transform.scaleV);
}



TransformComponent::Mobility TransformComponent::getMobility() const
{
	return mobility;
}



const Vec2f& TransformComponent::getGlobalPosition() const
{
	return globalTransform.position;
}

Vec2f TransformComponent::getRelativePosition() const
{
	if (parent)
		return globalTransform.position - parent->globalTransform.position;
	return globalTransform.position;
}

Vec2f TransformComponent::getLocalPosition() const
{
	if (parent)
		return globalTransform.position * asRotationMatrix(parent->globalTransform.rotation);
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



const Vec2f& TransformComponent::getGlobalScale() const
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



const Transform& TransformComponent::getGlobalTransform() const
{
	return globalTransform;
}

Transform TransformComponent::getRelativeTransform() const
{
	return Transform(getRelativePosition(), getRelativeRotation(), getRelativeScale());
}

Transform TransformComponent::getLocalTransform() const
{
	return Transform(getLocalPosition(), getRelativeRotation(), getRelativeScale());
}