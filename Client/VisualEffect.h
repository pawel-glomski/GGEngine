#pragma once
#include "Entity.h"
class VisualEffect : public Entity
{
public:
	virtual void onSpawn() override {}
	virtual void display(sf::RenderWindow & window) const override {}
	virtual void update(float_t deltaTime) override {}
};

