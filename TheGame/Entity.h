#pragma once
#include <SFML/Graphics.hpp>
#include "Vec2.h"

class Entity
{
public:
	virtual void spawn() = 0;
	virtual void display(sf::RenderWindow & window) = 0;
	void setPosition(const Vect2f & newPosition, bool sweep = false);
	void move(const Vect2f & translationVector, bool sweep = false);

	virtual ~Entity() = default;

private:
	Vect2f	position;
	bool	visible;
};

