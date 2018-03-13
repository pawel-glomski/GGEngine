#pragma once
#include <memory>
#include "stdInclude.h"
#include "TuplePlus.h"

// settings for a module (specialized in final modules)
template<class T>
class Settings {};

template<class ...DTypes> // DTypes = Dependencies (other modules)
class Module
{
protected:

	// base for inherting types
	using Base_t = Module<DTypes...>;
	
private:

	template<class T>
	using StdUPtr_t = std::unique_ptr<T>;

	using DHolder_t = TuplePlus< StdUPtr_t<DTypes>& ...>;

public:

	template<class ...MPtrTypes>
	Module(TuplePlus<MPtrTypes...> & modules) : dependencies(modules.asRefTuple<StdUPtr_t<DTypes>...>())	{}

	virtual ~Module() = default;


	virtual void startUp() {};

	virtual void update(float_t dt) {};

	virtual void shoutDown() { std::cout << std::type_index(typeid(*this)).name() << std::endl; };


protected:

	template<class T>
	T& getDependency() const
	{
		return *dependencies.get< StdUPtr_t<T>& >();
	}


private:

	const DHolder_t dependencies;

};