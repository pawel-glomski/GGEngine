#pragma once
#include "BasicObject.h"
#include "PhysicsComponent.h"
#include "ControllerComponent.h"
#include "SkeletonComponent.h"


class PlayerCharacter : public BasicObject<SkeletonComponent, ControllerComponent>
{
public:

	virtual void construct(ObjectModule& objectModule) override;

};