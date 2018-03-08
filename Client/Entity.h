#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_set>
#include "Transformation.h"

typedef int32_t EntityID;

/*
Entity instances can be created only by entity manager by spawn functions!
*/
class Entity
{
	friend class EntityManager;
public:
	// constructor is called on entity spawn, 
	Entity() = default;
	// destructor is called on entity destroy (destroyment of attached entities is handled by entity manager)
	virtual ~Entity() = default;

	EntityID getID();

	void setRelativeRotation(float_t rotation);

	void setGlobalRotation(float_t rotation);

	void rotate(float_t deltaRotation);

	void setRelativePosition(const Vect2f & newPosition);

	void setGlobalPosition(const Vect2f & newPosition);

	void moveInGlobal(const Vect2f & translationVector);

	void moveInLocal(const Vect2f & translationVector);

	void moveForward(float_t distance);

	void moveRight(float_t distance);


	float_t getRelativeRotation() const;

	float_t getGlobalRotation() const;

	Vect2f getRelativePosition() const;

	Vect2f getGlobalPosition() const;

	Vect2f getForwardVector() const;

	Vect2f getRightVector() const;

	const Transformation & getRelativeTransform() const;

	// only temp objects can be destroyed by this function!
	void destroy();

	virtual void display(sf::RenderWindow& window) const = 0;

protected:

	void attachTo(Entity* parent);

	void unattach() noexcept;

	virtual void update(float deltaTIme);

protected:
	Transformation relativeTransform;

	EntityID id = -1;

	bool destroyed = false;	

	Entity* parent = nullptr;

	std::unordered_set<Entity*> attached;
};

