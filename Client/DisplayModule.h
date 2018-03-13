#pragma once
#include "WindowModule.h"

class DisplayModule : public Module<WindowModule>
{


public:
	template<class ...MPtrTypes>
	DisplayModule(TuplePlus<MPtrTypes...> & modules) : Base_t(modules) {};

};

