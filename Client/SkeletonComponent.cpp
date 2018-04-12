#include "SkeletonComponent.h"
#include "ObjectModule.h"

void SkeletonComponent::construct(ObjectModule & objectModule)
{
	for(uint8_t i = uint8_t(JointIndex::Root); i < uint8_t(JointIndex::Count); i++)
		skeletonJoints[i] = objectModule.spawnObject<Joint_t>(IdScope::Local, Lifetime::Perm).getComponents();

	attachAllComponents(skeletonJoints[uint8_t(JointIndex::Root)], skeletonJoints[uint8_t(JointIndex::LeftHand)]);
	attachAllComponents(skeletonJoints[uint8_t(JointIndex::Root)], skeletonJoints[uint8_t(JointIndex::RightHand)]);
}

void SkeletonComponent::attachSkeletonIdentityToOwner(const CPtr_t<IdentityComponent>& skeletonOwner)
{
	skeletonOwner->attach(getJoint(JointIndex::Root).get<CPtr_t<IdentityComponent>>());
}

void SkeletonComponent::attachWeaponToJoint(const WeaponObject & weapon, JointIndex jointIndex)
{
	ASSERT(false, "TODO: Add weapon component, with data about weapon: is it one/two handed, etc. \
		Add component to joint type, so it will store all needed data about possibilities of that joint");
	attachAllComponents(skeletonJoints[uint8_t(jointIndex)], weapon.getComponents());
}

void SkeletonComponent::attachBodyPartToJoint(const BodyPartObject & bodyPart, JointIndex jointIndex)
{
	ASSERT(false, "TODO: Add component to joint type, so it will store all needed data about possibilities of that joint");
	attachAllComponents(skeletonJoints[uint8_t(jointIndex)], bodyPart.getComponents());
}

SkeletonComponent::JointCPack_t & SkeletonComponent::getJoint(JointIndex jointIndex)
{
	return skeletonJoints[uint8_t(jointIndex)];
}

const SkeletonComponent::JointCPack_t & SkeletonComponent::getJoint(JointIndex jointIndex) const
{
	return skeletonJoints[uint8_t(jointIndex)];
}