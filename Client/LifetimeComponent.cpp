#include "LifetimeComponent.h"
#include "stdInclude.h"

void LifetimeComponent::spawn()
{
	ASSERT((lifeState != LifeState::Alive), "Tried to spawn already alive entity");
	ASSERT((lifeState != LifeState::Dead || lifeState != LifeState::Dying), "Tried to spawn dead entity");
	if (lifeState == LifeState::Spawning)
		lifeState = LifeState::Alive;
}

bool LifetimeComponent::die()
{
	ASSERT((lifetime == Lifetime::Temp), "Tried to kill perm entity");
	ASSERT((lifeState == LifeState::Alive), "Tried to kill not-alive entity");
	if (lifetime == Lifetime::Temp && lifeState == LifeState::Alive)
		lifeState = LifeState::Dying;
	return lifeState == LifeState::Dying;
}

void LifetimeComponent::setLifetime(Lifetime lt)
{
	ASSERT((lifetime == Lifetime::None), "Tried to assign entity to Lifetime, while it is already asigned to one");
	if (lifetime == Lifetime::None)
		lifetime = lt;
}

bool LifetimeComponent::wasSpawned() const
{
	return (lifeState != LifeState::Spawning);
}

bool LifetimeComponent::isAlive() const
{
	return (lifeState == LifeState::Alive);
}

bool LifetimeComponent::isDying() const
{
	return (lifeState == LifeState::Dying);
}

LifeState LifetimeComponent::getLifeState() const
{
	return lifeState;
}

Lifetime LifetimeComponent::getLifeTime() const
{
	return lifetime;
}

void LifetimeComponent::destroy()
{
	ASSERT((lifeState == LifeState::Dying), "Tried to destroy entity that is not dying");
	if(lifeState == LifeState::Dying)
		lifeState = LifeState::Dead;
}
