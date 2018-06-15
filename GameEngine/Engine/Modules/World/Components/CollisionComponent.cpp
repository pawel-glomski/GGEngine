#include "CollisionComponent.h"


void CollisionComponent::addCollision(const CollisionData & collisionNode)
{
	collisions.push_back(collisionNode);
}

void CollisionComponent::clearCollisions()
{
	collisions.clear();
}

void CollisionComponent::setCollisionChannel(CollisionChannel channel)
{
	collisionChannel = channel;
}

void CollisionComponent::setCollisionChannels(uint32_t channels)
{
	collisionChannels = channels;
}

void CollisionComponent::addCollisionChannel(CollisionChannel channel)
{
	collisionChannels |= channel;
}

bool CollisionComponent::canCollideWith(const CollisionComponent & other) const
{
	return (collisionChannels & other.collisionChannel && other.collisionChannels & collisionChannel);
}

CollisionComponent::CollisionsHolder_t & CollisionComponent::getCollisions()
{
	return collisions;
}

const CollisionComponent::CollisionsHolder_t & CollisionComponent::getCollisions() const
{
	return collisions;
}

uint32_t CollisionComponent::getCollisionChannels() const
{
	return collisionChannels;
}

CollisionChannel CollisionComponent::getCollisionChannel() const
{
	return collisionChannel;
}
