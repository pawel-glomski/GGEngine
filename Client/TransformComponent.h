#pragma once
#include <memory>
#include "AttachableComponent.h"
#include "Transform.h"

// Attachment effects - from parent's perspective, attached components are static when his transform changes (they transform with him)
class TransformComponent : public AttachableComponent<TransformComponent>
{
public:

	// Describes if transformation can be changed
	// if entity is in-game static, TransformComponent's mobility member should be set to WorldStatic before first update after spawn, 
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


	void setRelativeTransform(const Transform& transform);

	void setGlobalTransform(const Transform& transform);


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

	const Transform& getGlobalTransform() const;

private:

	// when mobility turns WorldStatic, then transform will behave as there is no parent for this transform (faster getters functions)
	Mobility mobility = Mobility::Movable;


	Transform globalTransform;
};