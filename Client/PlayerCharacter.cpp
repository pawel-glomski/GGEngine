#include "PlayerCharacter.h"
#include "ObjectModule.h"
#include "LongswordObject.h"
#include "BodyPartObject.h"

void PlayerCharacter::construct(ObjectModule & objectModule)
{
	ObjectBase_t::construct(objectModule);

	getComponent<SkeletonComponent>().attachSkeletonIdentityToOwner(getComponentPtr<IdentityComponent>());

	// this should be done in some game loading/startup function

	auto & body = objectModule.spawnObject<BodyPartObject>(IdScope::Local, Lifetime::Perm);
	auto & weapon = objectModule.spawnObject<LongswordObject>(IdScope::Local, Lifetime::Perm);

	getComponent<SkeletonComponent>().attachWeaponToJoint(weapon, JointIndex::RightHand);
	getComponent<SkeletonComponent>().attachBodyPartToJoint(body, JointIndex::Root);
}
