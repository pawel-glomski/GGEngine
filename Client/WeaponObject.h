#pragma once
#include "BasicObject.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "CollisionComponent.h"
#include "DisplayComponent.h"

class WeaponObject : public BasicObject<TransformComponent, PhysicsComponent, CollisionComponent, DisplayComponent>
{

};