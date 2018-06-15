#pragma once
#include <ECSpp/Component.h>
#include "Utilities/Math/Transform.h"


class TransformComponent : public epp::Component
{
public:

	enum class Mobility
	{
		Movable,
		WorldStatic,
		RelativeStatic
	};

public:

	void setMobility(Mobility newMobility);


	void setRotation(float_t newRotation);

	void rotate(float_t rotation);


	void setScale(const Vec2f & newScale);

	void scale(const Vec2f & scaleV);


	void setPosition(const Vec2f & newPosition);

	void moveGlobal(const Vec2f & translation);

	void moveLocal(const Vec2f & translation);

	void moveForward(float_t distance);

	void moveRight(float_t distance);


	void setTransform(const Transform& transform);


	Mobility getMobility() const;


	const Vec2f& getPosition() const;

	float_t getRotation() const;

	const Vec2f& getScale() const;


	Vec2f getForwardVector() const;

	Vec2f getRightVector() const;


	const Transform& getTransform() const;

private:


	Mobility mobility = Mobility::Movable;

	Transform globalTransform;
};