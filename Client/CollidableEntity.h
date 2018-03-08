#pragma once
#include "Entity.h"
#include "CollisionShape.h"

class CollidableEntity : public Entity
{
public:
	//CollisionResult collideWith(CollidableEntity & entity);

	// load shape ...
	// ...
	virtual ~CollidableEntity() {}

	virtual void display(sf::RenderWindow & window) const override {}
	virtual void update(float_t deltaTime) override {}

private:
	
	CollisionShape collisionShape;
};

