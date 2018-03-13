#pragma once
#include "Module.h"


template<class ...MTypes>
class ModulesHolder
{
	template<class T>
	using StdUPtr_t = std::unique_ptr<T>;

	using DHolder_t = TuplePlus<StdUPtr_t<MTypes>...>;

public:


	ModulesHolder()
	{
		((modules.get<StdUPtr_t<MTypes>>() = std::make_unique<MTypes>(modules)), ...);
	}

	void startUp()
	{
		(getModule<MTypes>().startUp(), ...);
	}

	void update(float_t dt)
	{
		(getModule<MTypes>().update(dt), ...);
	}
	
	void shoutDown()
	{
		ASSERT(false, "Shout down wrong order (should be reversed)");
		shoutDownModules(getModule<MTypes>()...);
	}


	template<class T>
	T& getModule()
	{
		return *(modules.get<StdUPtr_t<T>>());
	}


	template<class T>
	const T& getModule() const
	{
		return *(modules.get<StdUPtr_t<T>>());
	}

private:

	// recursive function
	template<class T, class ...ModulesTypes>
	void shoutDownModules(T & module, ModulesTypes&... types)
	{
		shoutDownModules(types...);
		module.shoutDown();
	}
	void shoutDownModules() {}


private:

	DHolder_t modules;

};