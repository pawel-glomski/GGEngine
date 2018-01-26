#pragma once
#include "CollidableEntity.h"
#include "CharacterController.h"

class Character : public CollidableEntity
{
public:
	Character();
	~Character();

	virtual void onSpawn() override;
	virtual void display(sf::RenderWindow & window) const override;
	virtual void update(float_t deltaTime) override;

	Controller&		getController();
	const Controller&	getController() const;

private:
	Controller controller;
	
	sf::CircleShape displayShape;
};

