#include "DisplaySystem.h"

void DisplaySystem::update(float_t dt, const UsedMDepPack_t & dependencies, ObjectModule & objectModule)
{
	auto & displayModule = dependencies.get<MDep_t<DisplayModule>>();

	for (auto & cPackNode : objectsCPacks->getStdContainer())
	{
		auto & cPack = cPackNode.second;

		auto & display = cPack.get<CRef_t<DisplayComponent>>();
		auto & transform = cPack.get<CRef_t<TransformComponent>>();

		displayModule->drawWorldObject(display.getShape(), transform.getGlobalTransform(), display.getDisplayLevel());
	}
}
