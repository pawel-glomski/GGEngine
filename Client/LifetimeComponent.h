#pragma once
#include "Component.h"

enum class Lifetime : uint8_t { None, Temp, Perm };
enum class LifeState : uint8_t 
{ 
	Spawning, 
	Alive, 
	Dying,	// when entity was not yet set as deleted in entity manager
	Dead	// with this state, entity will be destroyed on before next update 
};

class LifetimeComponent :
	public Component
{
public:

	// changes state from Spawning to Alive
	void spawn();

	// kills entity (only if its temp entity)
	// returns true if killed
	bool die();


	void setLifetime(Lifetime lt);

	
	bool wasSpawned() const;

	bool isAlive() const;

	bool isDying() const;

	LifeState getLifeState() const;

	Lifetime getLifeTime() const;

private:

	// called by LifetimeSystem after calling EntityManager::destroyTempEntity
	void destroy();


private:

	Lifetime lifetime = Lifetime::None;

	LifeState lifeState = LifeState::Spawning;

	friend class LifetimeSystem;
};