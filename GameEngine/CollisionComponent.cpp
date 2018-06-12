#include "CollisionComponent.h"


void CollisionComponent::addCollision(const CollisionData & collisionNode)
{
	collisions.push_back(collisionNode);
}

void CollisionComponent::clearCollisions()
{
	collisions.clear();
}

void CollisionComponent::setCollisionChannels(uint16_t channels)
{
	collisionChannels = channels;
}

void CollisionComponent::addCollisionChannel(CollisionChannel channel)
{
	collisionChannels |= channel;
}

bool CollisionComponent::canCollideWith(const CollisionComponent & other) const
{
	if (!collideWithAttached && &getTopParent() == &other.getTopParent())
		return false;
	return (collisionChannels | other.collisionChannels);
}

const CollisionComponent::CollisionsHolder_t & CollisionComponent::getCollisions() const
{
	return collisions;
}

uint16_t CollisionComponent::getCollisionChannels() const
{
	return collisionChannels;
}
