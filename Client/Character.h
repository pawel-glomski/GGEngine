#pragma once
#include "CollidableEntity.h"
#include "Controller.h"

class Character : public CollidableEntity
{
public:
	Character();
	~Character();

	virtual void display(sf::RenderWindow & window) const override;
	virtual void update(float_t deltaTime) override;

	Controller&			getController();
	const Controller&	getController() const;

private:
	Controller controller;
	
	sf::CircleShape displayShape;
};

