#pragma once
#include <ECSpp/ECSWorld.h>
#include "Modules/Display/DisplayModule.h"
#include "Modules/Controller/ControllerModule.h"

class WorldModule : public Module<DisplayModule, ControllerModule>
{

public:

	template<class ...MTypes>
	WorldModule(const MDepPack_t<MTypes...> & dependencies) : ModuleBase_t(dependencies) {}


	virtual void startUp() override;

	virtual void update() override;

	virtual void shutdown() override;

public:

	epp::ECSWorld world;

};