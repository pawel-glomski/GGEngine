#pragma once
#include "Module.h"


template<class ...MTypes>
class ModulesHolder
{

	using MPack_t = TypesPack_t<StdUPtr_t<MTypes>...>;
 

public:


	ModulesHolder()
	{
		MDepPack_t<MTypes...> dependencies(modules.asRefTuple());
		((modules.get<StdUPtr_t<MTypes>>() = std::make_unique<MTypes>(dependencies)), ...);
	}

	void startUp()
	{
		(getModule<MTypes>().startUp(), ...);
	}

	void update(float_t dt)
	{
		(getModule<MTypes>().update(dt), ...);
	}
	
	void shutdown()
	{
		shutdownModules(getModule<MTypes>()...);
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
	void shutdownModules(T & module, ModulesTypes&... types)
	{
		shutdownModules(types...);
		module.shutdown();
	}
	void shutdownModules() {}


private:

	MPack_t modules;

};