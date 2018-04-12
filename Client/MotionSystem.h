#pragma once
#include "System.h"
#include "SkeletonComponent.h"
#include "ControllerComponent.h"


class MotionSystem : public System<MDepPack_t<>, CRefPack_t<SkeletonComponent, ControllerComponent>>
{
public:

	virtual void update(float_t dt, const UsedMDepPack_t& dependencies, ObjectModule & objectModule) override;

};


template<>
struct Settings<MotionSystem>
{

};