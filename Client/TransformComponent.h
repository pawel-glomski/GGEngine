#pragma once
#include <memory>
#include "MathUtilities.h"
#include "Component.h"

class TransformComponent : 
	public Component
{
public:

	struct Transform
	{
		Vec2f position;

		float_t rotation = 0;

		Vec2f scaleV = Vec2f::oneVector;

		Transform() = default;
		Transform(Vec2f position, float_t rotation, Vec2f scaleV) : position(position), rotation(rotation), scaleV(scaleV) {}
	};

	// Describes if transform member can be changed
	// if entity is in-game static, then TransformComponent's mobility member should be set to WorldStatic before first update after spawn, 
	// so systems can make some optimization.
	// Once mobility is set to WorldStatic, it shouldn't be changed back to any other mobility type 
	// (systems may work with false data because of it, but thats only true for entities that were WorldStatic while adding them to systems (on first update after spawn)
	// so if entity turns WorldStatic after that, systems will still see it as Movable and all data will remain valid)
	enum class Mobility
	{
		Movable,		// Can freely change entity's transform
		WorldStatic,	// Entity will remain still in world (even when attached to moving parent)
		RelativeStatic	// Entity will remain still relative to the parent's transform
	};

public:

	void setMobility(Mobility newMobility);


	void setGlobalRotation(float_t newRotation);

	void setRelativeRotation(float_t newRotation);

	void rotate(float_t rotation);


	void setGlobalScale(const Vec2f & newScale);

	void setRelativeScale(const Vec2f & newScale);

	void scale(const Vec2f & scaleV);


	void setGlobalPosition(const Vec2f & newPosition);

	void setRelativePosition(const Vec2f & newPosition);

	// moves in global coordinate system (based on global rotation)
	void moveGlobal(const Vec2f & translation);

	// moves in local coordinate system (based on global rotation)
	void moveLocal(const Vec2f & translation);

	// moves forward in local coordinate system (based on global rotation)
	void moveForward(float_t distance);

	// moves right in local coordinate system (based on global rotation)
	void moveRight(float_t distance);



	Mobility getMobility() const;


	Vec2f getGlobalPosition() const;

	Vec2f getRelativePosition() const;


	float_t getGlobalRotation() const;

	float_t getRelativeRotation() const;


	Vec2f getGlobalScale() const;

	Vec2f getRelativeScale() const;


	Vec2f getForwardVector() const;

	Vec2f getRightVector() const;


	Transform getRelativeTransform() const;

	Transform getGlobalTransform() const;

	
	void setParentTransform(const TransformComponent * parentTransform);


	void resetParentTransform();

private:

	// when mobility turns WorldStatic, then transform will behave as there is no parent for this transform
	Mobility mobility = Mobility::Movable;


	Transform relativeTransform;


	// Relation component manages this variable (on attach, unattach, object destruction) 
	const TransformComponent* parentTransform = nullptr;

	// takes value of parentTransform when Mobility turns WorldStatic, so that when Mobility turns back to non-WorldStatic
	// it can give parentTransform its old value
	const TransformComponent* parentTransformCopy = nullptr;
};

Matrix asRotationMatrix(float_t rotation);

Matrix asTranslationMatrix(const Vec2f & translation);

Matrix asScaleMatrix(const Vec2f & scale);

Vec2f forwardVectorFromRotation(const Matrix & rotationM);

Vec2f forwardVectorFromRotation(float_t rotation);

Vec2f rightVectorFromRotation(const Matrix & rotationM);

Vec2f rightVectorFromRotation(float_t rotation);