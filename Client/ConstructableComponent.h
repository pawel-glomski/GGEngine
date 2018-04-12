#pragma once
#include "IdentityComponent.h"

class ObjectModule;

struct ConstructableComponent : public Component
{
	virtual void construct(ObjectModule& objectModule) = 0;
};