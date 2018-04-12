#pragma once
#include "WeaponObject.h"
#include "BodyPartObject.h"


enum class JointIndex : uint8_t { Root, LeftHand, RightHand, Count };


class SkeletonComponent : public ConstructableComponent
{

	using Joint_t = BasicObject<TransformComponent, PhysicsComponent, CollisionComponent>;

	using JointCPack_t = Joint_t::UsedCPack_t;

public:

	virtual void construct(ObjectModule& objectModule) override;


	// share lifetime with...
	void attachSkeletonIdentityToOwner(const CPtr_t<IdentityComponent>& skeletonOwner);


	void attachWeaponToJoint(const WeaponObject& weapon, JointIndex jointIndex);

	void attachBodyPartToJoint(const BodyPartObject& bodyPart, JointIndex jointIndex);


	JointCPack_t& getJoint(JointIndex jointIndex);

	const JointCPack_t& getJoint(JointIndex jointIndex) const;


private:

	JointCPack_t skeletonJoints[uint8_t(JointIndex::Count)];

};