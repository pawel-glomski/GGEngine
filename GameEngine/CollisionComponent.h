#pragma once
#include <vector>
#include <ECSpp/EntityManager/EntityRef.h>
#include "MathUtilities.h"


enum CollisionChannel
{
	C_None		= 0b0,
	C_Static	= 0b1,
	C_Dynamic	= 0b10,
	C_Every		= 0xFFFFFFFF
};


struct CollisionData
{
	epp::EntityRef entity;

	Vec2f collisionPoint;

	Vec2f normal;

	float magnitude = 0;
};


class CollisionComponent : public epp::Component
{

	using CollisionsHolder_t = std::vector<CollisionData>;


public:

	void addCollision(const CollisionData& collisionNode);

	void clearCollisions();


	void setCollisionChannels(uint32_t channels);

	void addCollisionChannel(CollisionChannel channel);


	bool canCollideWith(const CollisionComponent& other) const;


	const CollisionsHolder_t& getCollisions() const;

	uint32_t getCollisionChannels() const;


private:

	uint32_t collisionChannels = C_Every;

	CollisionsHolder_t collisions;

};
