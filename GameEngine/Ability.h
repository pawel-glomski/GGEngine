#pragma once
#include <corecrt_math.h>
#include <cstdint>
#include <typeindex>
#include <vector>
#include <memory>
#include "MathUtilities.h"

class EntityManager;

class Ability
{
public:
	enum class ExecutionStage : uint8_t
	{
		// when ability starts execution (changes to MidWay in first execution call)
		Beginning,

		/*when ability is executing input-dependend stage (only in this stage, player can change ability behaviour by releasing button)
		(changes to Ending on player button release, or ability by itself after reaching the last stage of execution) */
		InputDependend,

		// when ability is executing the last stage, or when player released button
		Ending
	};

public:

	// first call inits every Ability index
	// global ids of abilities are used to indentify ability on both, client and server side 
	// (both applicatons are using the same code file, so indices always matches)
	static const Ability* getStaticInstanceByGlobalID(size_t id);

	virtual const Ability* getStaticInstance() const = 0;

	virtual std::unique_ptr<Ability> makeInstance() const = 0;


	// gets entityManager only for spawning new entities (like projectiles and stuff)
	virtual bool execute(EntityManager & entityManager, Entity & entity, float_t dt) = 0;

	
	void endInputDependendStage();

	bool finishedExecuting() const;

protected:

	static std::vector<const Ability*> staticInstancesIndices;


	float_t fullExecutionTime = 0.f;

	float_t executingTime = 0.f;

	ExecutionStage stage = ExecutionStage::Beginning;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AbilityBase

template<class T>
class AbilityBase : public Ability
{
public:

	virtual const Ability* getStaticInstance() const override;

	virtual std::unique_ptr<Ability> makeInstance() const override;
};

template<class T>
inline const Ability * AbilityBase<T>::getStaticInstance() const
{
	static T staticInstance;
	return &staticInstance;
}

template<class T>
inline std::unique_ptr<Ability> AbilityBase<T>::makeInstance() const
{
	return std::make_unique<T>();
}

// AbilityBase
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class UndefinedAbility : public AbilityBase<UndefinedAbility>
{
public:
	//virtual bool execute(EntityManager & entityManager, Entity & entity, float_t dt) override;
	virtual bool execute(EntityManager & entityManager, Entity & entity, float_t dt) override;
};

class RotateAbility : public AbilityBase<RotateAbility>
{
public:
	virtual bool execute(EntityManager & entityManager, Entity & entity, float_t dt) override;

	bool bRotate = true;
};

class WalkForwardAbility : public AbilityBase<WalkForwardAbility>
{
public:
	virtual bool execute(EntityManager & entityManager, Entity & entity, float_t dt) override;
};

class WalkBackwardAbility : public AbilityBase<WalkBackwardAbility>
{
public:
	virtual bool execute(EntityManager & entityManager, Entity & entity, float_t dt) override;
};

class WalkLeftAbility : public AbilityBase<WalkLeftAbility>
{
public:
	virtual bool execute(EntityManager & entityManager, Entity & entity, float_t dt) override;
};

class WalkRightAbility : public AbilityBase<WalkRightAbility>
{
public:
	virtual bool execute(EntityManager & entityManager, Entity & entity, float_t dt) override;
};

class DashAbility : public AbilityBase<DashAbility>
{
public:
	DashAbility();

	virtual bool execute(EntityManager & entityManager, Entity & entity, float_t dt) override;
private:

	float_t distanceToTravel = 0;
	float_t traveledDistance = 0;
};
