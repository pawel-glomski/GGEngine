#pragma once
#include <memory>
#include <unordered_set>
#include "System.h"
#include "DisplayModule.h"
#include "TransformComponent.h"
#include "DisplayComponent.h"

class DisplaySystem : public System<MDepPack_t<DisplayModule>, CRefPack_t<DisplayComponent, TransformComponent>>
{
public:

	virtual void update(float_t dt, const UsedMDepPack_t& dependencies, ObjectModule& objectModule) override;

};