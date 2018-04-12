#pragma once
#include "System.h"
#include "CollisionComponent.h"
#include "TransformComponent.h"

class CollisionSystem : public System<MDepPack_t<>, CRefPack_t<CollisionComponent, TransformComponent>>
{
	virtual void update(float_t dt, const UsedMDepPack_t& dependencies, ObjectModule & objectModule) override;
};