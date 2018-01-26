#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>
#include "Vec2.h"

class Entity
{
public:
	Entity();
	virtual ~Entity();

	void selfDestroy();

	void setName(std::string newName);
	std::string getName();

	// set position relative to parent's position
	void setRelativePosition(const Vect2f & newPosition, bool sweep = false);
	void setGlobalPosition(const Vect2f & newPosition, bool sweep = false);

	void moveInGlobal(const Vect2f & translationVector, bool sweep = false);	// useless on client side, only used on server side
	// move relative to entity's local coordinate system
	void moveInLocal(const Vect2f & translationVector, bool sweep = false);		// useless on client side, only used on server side

	Vect2f getRelativePosition() const;
	Vect2f getGlobalPosition() const;

	virtual void display(sf::RenderWindow& window) const = 0;

protected:	
	void attachTo(Entity* parent);
	void unattach();

	// spawn class-specific attached entities here
	virtual void constructComplexEntity(class EntityManager& entityManager);
	virtual void update(float deltaTIme);
	virtual void onDestroy();
	// callen when class-specific attached entities are spawned
	virtual void onSpawn() = 0;

private:
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
	std::vector<Entity*> attached;

	friend class EntityManager;
};

