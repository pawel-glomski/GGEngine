#pragma once
#include "AttachableComponent.h"
#include "Transform.h"

// used units: meter, second, kg, radian

struct TranslationData
{
	Vec2f local;
	Vec2f global;
	float_t angular = 0.f;

	bool operator==(const TranslationData& rhs)
	{
		return (local == rhs.local && global == rhs.global && angular == rhs.angular);
	}

	bool operator!=(const TranslationData& rhs)
	{
		return !(*this == rhs);
	}

	TranslationData operator*(float_t rhs) const
	{
		TranslationData result;
		result.local = local * rhs;
		result.global = global * rhs;
		result.angular = angular * rhs;
		return result;
	}

	TranslationData operator+(const TranslationData & rhs) const
	{
		TranslationData result;
		result.local = local + rhs.local;
		result.global = global + rhs.global;
		result.angular = angular + rhs.angular;
		return result;
	}

	TranslationData& operator*=(float_t rhs)
	{
		return (*this = (*this * rhs));
	}

	TranslationData& operator+=(const TranslationData & rhs)
	{
		return (*this = (*this + rhs));
	}
};


// attach effect - parent's global mass consists of all attached entitites' global masses, 
// attached PhysicsComponents changes their global data with parent, but parent doesn't change its data with childrens
class PhysicsComponent : public AttachableComponent<PhysicsComponent>
{

public:

	void addAccelerations(const TranslationData& toAdd)
	{
		accelerations += toAdd;
	}

	void resetAccelerations()
	{
		accelerations = TranslationData();
	}

	void resetVelocitites()
	{
		velocities = TranslationData();
	}

	void resetAllTranslationData()
	{
		resetAccelerations();
		resetVelocitites();
	}


	void applyAccelerations(float_t dt)
	{
		velocities += accelerations * dt;
	}

	float_t getLocalMass() const
	{
		return mass;
	}

	float_t getGlobalMass() const
	{
		if (attached.empty())
			return mass;

		float_t globalMass = mass;
		for (auto & child : attached)
			globalMass += child->getGlobalMass();
		
		return globalMass;
	}


	const TranslationData& getLocalVelocities() const
	{
		return velocities;
	}

	TranslationData getGlobalVelocities() const
	{
		if (parent)
			return parent->getGlobalVelocities() + velocities;
		return velocities;
	}

	const TranslationData& getLocalAccelerations() const
	{
		return accelerations;
	}

	TranslationData getGlobalAccelerations() const
	{
		if (parent)
			return parent->getGlobalAccelerations() + accelerations;
		return accelerations;
	}

private:

	TranslationData accelerations;

	TranslationData velocities;

	float_t mass = 1.f;

};