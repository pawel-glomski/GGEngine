#pragma once
#include "ECSpp/Component.h"
#include "MathUtilities.h"

struct PhysicsComponent : public epp::Component
{
	Vec2f velocity;
	float mass;
	float rotationVelocity;
};

