#include "CollisionSystem.h"

void CollisionSystem::update(float_t dt, const UsedMDepPack_t & dependencies, ObjectModule & objectModule)
{
	for (auto & cPackNode : objectsCPacks->getStdContainer())
	{
		auto & cPack = cPackNode.second;
		auto & transformC = cPack.get<CRef_t<TransformComponent>>();
		auto & collisionC = cPack.get<CRef_t<CollisionComponent>>();

		//collisionC.
	}
}
