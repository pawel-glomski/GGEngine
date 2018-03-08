#pragma once
#include "Entity.h"

class AudioEffect : public Entity
{
public:
	virtual void display(sf::RenderWindow & window) const override {}
	virtual void update(float_t deltaTime) override {}
};

