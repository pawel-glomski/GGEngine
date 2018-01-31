#pragma once
#include "CollidableEntity.h"

class Projectile : public CollidableEntity
{
public:
	virtual void onSpawn() override {}
	virtual void display(sf::RenderWindow & window) const override {}
	virtual void update(float_t deltaTime) override{}
};

