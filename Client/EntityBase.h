#pragma once
#include "Component.h"

struct EntityBase
{
	EntityBase() = default;
	virtual ~EntityBase() = default;

	virtual void uniqueUpdate(float_t dt)
	{}
};