#pragma once
#include "BasicObject.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "DisplayComponent.h"
#include "CollisionComponent.h"

class BodyPartObject : public BasicObject<TransformComponent, PhysicsComponent, DisplayComponent, CollisionComponent>
{

};