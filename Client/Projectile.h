#pragma once
#include "CollidableEntity.h"

class Projectile : public CollidableEntity
{
public:
	virtual void spawn(const Vect2f & position, std::weak_ptr<Entity> parent = std::weak_ptr<Entity>()) {}
	virtual void display(sf::RenderWindow & window) const override {}
	virtual void update(float_t deltaTime) {}
};

