#include "Ability.h"
#include "AbilitySystem.h"
#include "EntityManager.h"
#include "Entity.h"

std::vector<const Ability*> Ability::staticInstancesIndices;

const Ability* Ability::getStaticInstanceByGlobalID(size_t id)
{
	bool firstCall = true;
	if (firstCall)
	{
		staticInstancesIndices.push_back(RotateAbility().getStaticInstance());
		staticInstancesIndices.push_back(WalkForwardAbility().getStaticInstance());
		staticInstancesIndices.push_back(WalkBackwardAbility().getStaticInstance());
		staticInstancesIndices.push_back(WalkLeftAbility().getStaticInstance());
		staticInstancesIndices.push_back(WalkRightAbility().getStaticInstance());
		staticInstancesIndices.push_back(DashAbility().getStaticInstance());

		firstCall = false;
	}

	if (id < staticInstancesIndices.size())
		return staticInstancesIndices[id];
	ASSERT((id < staticInstancesIndices.size()), "Tried to get type intex with unidenftified id! Returned UndefinedAbility. Bad id = " + std::to_string(id));
	return UndefinedAbility().getStaticInstance();
}

void Ability::endInputDependendStage()
{
	if (stage == ExecutionStage::InputDependend)
		stage = ExecutionStage::Ending;
}

bool Ability::finishedExecuting() const
{
	return 	(executingTime >= fullExecutionTime && stage == ExecutionStage::Ending);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool UndefinedAbility::execute(EntityManager & entityManager, Entity & entity, float_t dt)
{
	std::cout << "Executes no action" << std::endl;
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool RotateAbility::execute(EntityManager & entityManager, Entity & entity, float_t dt)
{
	if (bRotate)
	{
		auto transformComponent = entity.getComponent<TransformComponent>();
		auto controllerComponent = entity.getComponent<ControllerComponent>();

		float_t delta = controllerComponent->joystickRotation - transformComponent->getGlobalRotation();
		if (delta != 0)
			transformComponent->rotate(delta);
	}
	// never ends
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool WalkForwardAbility::execute(EntityManager & entityManager, Entity & entity, float_t dt)
{
	auto transformComponent = entity.getComponent<TransformComponent>();

	if (stage == ExecutionStage::Beginning)
		stage = ExecutionStage::InputDependend;

	transformComponent->moveForward(1.5f * dt);

	return finishedExecuting();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool WalkBackwardAbility::execute(EntityManager & entityManager, Entity & entity, float_t dt)
{
	auto transformComponent = entity.getComponent<TransformComponent>();

	if (stage == ExecutionStage::Beginning)
		stage = ExecutionStage::InputDependend;

	transformComponent->moveForward(-1.5f * dt);


	return finishedExecuting();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool WalkRightAbility::execute(EntityManager & entityManager, Entity & entity, float_t dt)
{
	auto transformComponent = entity.getComponent<TransformComponent>();

	if (stage == ExecutionStage::Beginning)
		stage = ExecutionStage::InputDependend;

	transformComponent->moveRight(1.5f * dt);


	return finishedExecuting();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool WalkLeftAbility::execute(EntityManager & entityManager, Entity & entity, float_t dt)
{
	auto transformComponent = entity.getComponent<TransformComponent>();

	if (stage == ExecutionStage::Beginning)
		stage = ExecutionStage::InputDependend;

	transformComponent->moveRight(-1.5f * dt);


	return finishedExecuting();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

DashAbility::DashAbility()
{
	fullExecutionTime = 10; // doesn't matter, executes until will travel specified distance
}

bool DashAbility::execute(EntityManager & entityManager, Entity & entity, float_t dt)
{
	auto transformComponent = entity.getComponent<TransformComponent>();
	auto controllerComponent = entity.getComponent<ControllerComponent>();
	auto abilityComponent = entity.getComponent<AbilityComponent>();

	const float_t maxDistanceToTravel = 10;
	if (stage == ExecutionStage::Beginning)
	{
		distanceToTravel = controllerComponent->joystickPositionOffset;
		clamp(distanceToTravel, 0.f, maxDistanceToTravel);

		stage = ExecutionStage::Ending;
		static_cast<RotateAbility*>(abilityComponent->executingAbilities[getStaticInstanceByGlobalID(0)].get())->bRotate = 0;
	}

	executingTime += dt;

	float_t distance = 15 * dt;
	clamp(distance, 0.f, distanceToTravel - traveledDistance);
	traveledDistance += distance;
	transformComponent->moveForward(distance);
	if (distanceToTravel - traveledDistance == 0)
	{
		executingTime = fullExecutionTime;
		static_cast<RotateAbility*>(abilityComponent->executingAbilities[RotateAbility().getStaticInstance()].get())->bRotate = 1;
	}
	return finishedExecuting();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////