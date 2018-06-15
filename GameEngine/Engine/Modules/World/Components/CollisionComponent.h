#pragma once
#include <vector>
#include <ECSpp/EntityManager/EntityRef.h>
#include "Utilities/Math/MathUtilities.h"
#include "Utilities/ThirdParty/tinyc2.h"


enum CollisionChannel
{
	C_None		= 0b0,
	C_Static	= 0b1,
	C_Dynamic	= 0b10,
	C_Every		= 0xFFFFFFFF
};

struct MyManifold
{
	MyManifold() = default;
	MyManifold(c2Manifold c2) : count(c2.count), depths{ c2.depths[0], c2.depths[1] }, contact_points{ asVec<Vec2f>(c2.contact_points[0]), asVec<Vec2f>(c2.contact_points[1]) }, n(asVec<Vec2f>(c2.n))
	{}

	size_t count = 0;
	float depths[2];
	Vec2f contact_points[2];
	Vec2f n;
};

struct CollisionData
{
	epp::EntityRef entity;
	
	MyManifold manifold;
};


class CollisionComponent : public epp::Component
{

	using CollisionsHolder_t = std::vector<CollisionData>;


public:

	void addCollision(const CollisionData& collisionNode);

	void clearCollisions();


	void setCollisionChannel(CollisionChannel channel);

	void setCollisionChannels(uint32_t channels);

	void addCollisionChannel(CollisionChannel channel);


	bool canCollideWith(const CollisionComponent& other) const;


	CollisionsHolder_t& getCollisions();

	const CollisionsHolder_t& getCollisions() const;


	uint32_t getCollisionChannels() const;

	CollisionChannel getCollisionChannel() const;

private:

	CollisionChannel collisionChannel = C_Dynamic;

	uint32_t collisionChannels = C_Every;

	CollisionsHolder_t collisions;

};
