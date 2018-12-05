#pragma once
#include "Module.h"


template<class ...MTypes>
class ModulesManager
{

	using MPack_t = epp::TuplePP<StdUPtr_t<MTypes>...>;
 

public:
	

	ModulesManager()
	{
		MDepPack_t<MTypes...> dependencies(modules.asRefTuple());
		((modules.get<StdUPtr_t<MTypes>>() = std::make_unique<MTypes>(dependencies)), ...);
	}

	void startUp()
	{
		(getModule<MTypes>().startUp(), ...);
	}

	void update()
	{
		(getModule<MTypes>().update(), ...);
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

	// recursive function for reversed modules shoutdown order
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