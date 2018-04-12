#pragma once
#include <memory>
#include "TuplePlus.h"

template<class T>
using CPtr_t = std::shared_ptr<T>;

template<class T>
using CRef_t = T&;

template<class ...CTypes>
using CPack_t = TypesPack_t<CPtr_t<CTypes>...>;

template<class ...CTypes>
using CRefPack_t = TypesPack_t<CRef_t<CTypes>...>;


struct Component
{
	Component() = default;

	virtual ~Component()
	{
		onDestroy();
	}

	virtual void onDestroy()
	{}



};