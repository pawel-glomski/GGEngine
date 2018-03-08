#include "TransformComponent.h"

void TransformComponent::setMobility(Mobility newMobility)
{
	if (mobility == newMobility)
		return;

	if (mobility == Mobility::WorldStatic)
	{
		if (parentTransformCopy)
		{
			parentTransform = parentTransformCopy;
			relativeTransform.position -= parentTransform->getGlobalPosition();
			relativeTransform.rotation -= parentTransform->getGlobalRotation();
			auto parentScale = parentTransform->getGlobalScale();
			if (parentScale.x && parentScale.y)
			{
				relativeTransform.scaleV.x /= parentScale.x;
				relativeTransform.scaleV.y /= parentScale.y;
			}
			else
				relativeTransform.scaleV = Vec2f::zeroVector;
		}
	}
	else if (parentTransform && newMobility == Mobility::WorldStatic)
	{
		relativeTransform = getGlobalTransform();
		parentTransformCopy = parentTransform;
		parentTransform = nullptr;
	}
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

	if (parentTransform)
		setRelativeRotation(newRotation - parentTransform->getGlobalRotation());
	else
		setRelativeRotation(newRotation);
}

void TransformComponent::setRelativeRotation(float_t newRotation)
{
	if (mobility != Mobility::Movable)
		return;
	relativeTransform.rotation = newRotation;
}

void TransformComponent::rotate(float_t deltaRotation)
{
	if (mobility != Mobility::Movable)
		return;
	setRelativeRotation(relativeTransform.rotation + deltaRotation);
}

void TransformComponent::setGlobalPosition(const Vec2f & newPosition)
{
	if (mobility != Mobility::Movable)
		return;
	if (parentTransform)
		setRelativePosition(newPosition - parentTransform->getGlobalPosition());
	else
		setRelativePosition(newPosition);
}

void TransformComponent::setRelativePosition(const Vec2f & newPosition)
{
	if (mobility != Mobility::Movable)
		return;
	relativeTransform.position = newPosition;
}

void TransformComponent::moveGlobal(const Vec2f & translation)
{
	if (mobility != Mobility::Movable)
		return;
	relativeTransform.position += translation;
}

void TransformComponent::moveLocal(const Vec2f & translation)
{
	if (mobility != Mobility::Movable)
		return;
	moveGlobal(translation * asRotationMatrix(getGlobalRotation()));
}

void TransformComponent::moveForward(float_t distance)
{
	if (mobility != Mobility::Movable)
		return;
	moveLocal({ distance, 0 });
}

void TransformComponent::moveRight(float_t distance)
{
	if (mobility != Mobility::Movable)
		return;
	moveLocal({ 0, distance });
}

void TransformComponent::setGlobalScale(const Vec2f & newScale)
{
	if (mobility != Mobility::Movable)
		return;
	if (parentTransform)
		setRelativeScale({ newScale.x / parentTransform->getGlobalScale().x, newScale.y / parentTransform->getGlobalScale().y });
	else
		setRelativeScale(newScale);
}

void TransformComponent::setRelativeScale(const Vec2f & newScale)
{
	if (mobility != Mobility::Movable)
		return;
	relativeTransform.scaleV = newScale;
}

void TransformComponent::scale(const Vec2f & scaleV)
{
	if (mobility != Mobility::Movable)
		return;
	relativeTransform.scaleV.x *= scaleV.x;
	relativeTransform.scaleV.y *= scaleV.y;
}

TransformComponent::Mobility TransformComponent::getMobility() const
{
	return mobility;
}

Vec2f TransformComponent::getGlobalPosition() const
{
	if (parentTransform)
		return parentTransform->getGlobalPosition() + relativeTransform.position * asRotationMatrix(parentTransform->getGlobalRotation());
	return relativeTransform.position;
}

Vec2f TransformComponent::getRelativePosition() const
{
	if (mobility != Mobility::WorldStatic || !parentTransformCopy)
		return relativeTransform.position;
	else
		return relativeTransform.position - parentTransformCopy->getGlobalPosition();
}

float_t TransformComponent::getGlobalRotation() const
{
	if (parentTransform)
		return parentTransform->getGlobalRotation() + relativeTransform.rotation;
	return relativeTransform.rotation;
}

float_t TransformComponent::getRelativeRotation() const
{
	if (mobility != Mobility::WorldStatic || !parentTransformCopy)
		return relativeTransform.rotation;
	else
		return relativeTransform.rotation - parentTransformCopy->getGlobalRotation();
}

Vec2f TransformComponent::getGlobalScale() const
{
	if (parentTransform)
		return Vec2f(parentTransform->getGlobalScale().x * relativeTransform.scaleV.x, parentTransform->getGlobalScale().y * relativeTransform.scaleV.y);
	return relativeTransform.scaleV;
}

Vec2f TransformComponent::getRelativeScale() const
{
	if (mobility != Mobility::WorldStatic || !parentTransformCopy)
		return relativeTransform.scaleV;
	else
	{
		auto relativeScale = relativeTransform.scaleV;
		auto parentScale = parentTransformCopy->getGlobalScale();
		if (parentScale.x && parentScale.y)
		{
			relativeScale.x /= parentScale.x;
			relativeScale.y /= parentScale.y;
		}
		else
			relativeScale = Vec2f::zeroVector;
		return relativeScale;
	}
}

Vec2f TransformComponent::getForwardVector() const
{
	return forwardVectorFromRotation(getGlobalRotation());
}

Vec2f TransformComponent::getRightVector() const
{
	return rightVectorFromRotation(getGlobalRotation());
}

TransformComponent::Transform TransformComponent::getRelativeTransform() const
{
	if (mobility != Mobility::WorldStatic || !parentTransformCopy)
		return relativeTransform;
	else
		return Transform(getRelativePosition(), getRelativeRotation(), getRelativeScale());
}

TransformComponent::Transform TransformComponent::getGlobalTransform() const
{
	return Transform(getGlobalPosition(), getGlobalRotation(), getGlobalScale());
}

void TransformComponent::setParentTransform(const TransformComponent * parentTransform)
{
	ASSERT(parentTransform, "Tried to set transform parent as nullptr");
	ASSERT(!this->parentTransform, "Tried to set new transform parent, while transform already has one. To set transform's new parent, call resetParentTransform first");
	if (parentTransform && !this->parentTransform)
		this->parentTransform = parentTransform;
}

void TransformComponent::resetParentTransform()
{
	if (parentTransform)
		relativeTransform = getGlobalTransform();

	parentTransform = nullptr;
	parentTransformCopy = nullptr;
}

// utilities:

Matrix asTranslationMatrix(const Vec2f & translation)
{
	Matrix translationM;
	translationM(2, 0) = translation.x;
	translationM(2, 1) = translation.y;
	return translationM;
}

Matrix asScaleMatrix(const Vec2f & scale)
{
	Matrix scaleM;
	scaleM(0, 0) = scale.x;
	scaleM(1, 1) = scale.y;
	return scaleM;
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

Vec2f forwardVectorFromRotation(const Matrix & rotationM)
{
	return Vec2f(rotationM(0, 0), rotationM(0, 1)).normalized();
}

Vec2f forwardVectorFromRotation(float_t rotation)
{
	return forwardVectorFromRotation(asRotationMatrix(rotation));
}

Vec2f rightVectorFromRotation(const Matrix & rotationM)
{
	return Vec2f(rotationM(1, 0), rotationM(1, 1)).normalized();
}

Vec2f rightVectorFromRotation(float_t rotation)
{
	return rightVectorFromRotation(asRotationMatrix(rotation));
}