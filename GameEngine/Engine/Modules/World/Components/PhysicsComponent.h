#pragma once
#include "ECSpp/Component.h"
#include "Utilities/Math/MathUtilities.h"

struct PhysicsComponent : public epp::Component
{
	void setMass(float newMass)
	{
		mass = newMass;
		massInv = mass != 0.f ? 1.f / mass : 0.f;
		if (mass == 0.f)
		{
			moi = 0.f;
			moiInv = 0.f;
		}
	}



	void applyImpulse(const Vec2f& impulse, const Vec2f& contactVector)
	{
		velocity += massInv * impulse;
		angularVelocity += moiInv * crossProduct(contactVector, impulse);
	}

	Vec2f velocity;	
	float angularVelocity = 0.f;

	float mass = 1.f;
	float massInv = 1.f;

	float moi = 5.f;  // moment of inertia
	float moiInv = 0.2f; // inverse inertia

	float restitution = 0.2f;
	float staticFriction = 0.6f;
	float dynamicFriction = 0.4f;

};

