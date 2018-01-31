#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_set>
#include "Vec2.h"

class Entity
{
public:
	Entity();
	virtual ~Entity();

	void setName(std::string newName);
	std::string getName();

	// set position relative to parent's position
	void setRelativePosition(const Vect2f & newPosition, bool sweep = false);
	void setGlobalPosition(const Vect2f & newPosition, bool sweep = false);

	void moveInGlobal(const Vect2f & translationVector, bool sweep = false);
	// move relative to entity's local coordinate system
	void moveInLocal(const Vect2f & translationVector, bool sweep = false);

	Vect2f getRelativePosition() const;
	Vect2f getGlobalPosition() const;

	virtual void display(sf::RenderWindow& window) const = 0;

protected:	
	void attachTo(Entity* parent);
	void unattach();

	// called when class-specific attached entities are already spawned
	virtual void onSpawn() = 0;
	// spawn class-specific attached entities here
	virtual void constructComplexEntity(class EntityManager& entityManager);
	virtual void update(float deltaTIme);

	// if entity is destroyed in EntityManager, all attached entities will be destroyed there also
	virtual void onDestroy();


private:
	void selfDestroy();

	void updateRelativelPosition();
	void updateGlobalPosition();

protected:
	std::string name;
	bool selfDestroyed = false;	

	// make new class for this
	/////////////////////////////////////////
	Vect2f relativePosition;
	Vect2f globalPosition;
	float_t rotation = 0;
	/////////////////////////////////////////
	Entity* parent = nullptr;
	std::unordered_set<Entity*> attached;

	friend class EntityManager;
};

