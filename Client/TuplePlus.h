#pragma once
#include <tuple>
#include "stdInclude.h"

template<class T, class ...Pack>
inline constexpr bool isTypeInPack()
{
	return (std::is_same_v<T, Pack> || ...);
}

template<class ...Types>
struct TuplePlus : public std::tuple<Types...>
{

	using Base_t = std::tuple<Types...>;


	TuplePlus() = default;

	TuplePlus(const TuplePlus<Types...>&) = default;

	TuplePlus(const Base_t& rhs) : Base_t(rhs) {}


	template<class U>
	U& get();

	template<class U>
	const U& get() const;


	template<class ...OtherTypes>
	TuplePlus<OtherTypes...> asTuple();

	template<class ...OtherTypes>
	TuplePlus<OtherTypes...> asTuple() const;

	template<class ...OtherTypes>
	TuplePlus<OtherTypes&...> asRefTuple();

	template<class ...OtherTypes>
	TuplePlus<const OtherTypes&...> asRefTuple() const;


	template<class T>
	static constexpr bool containsType()
	{
		return isTypeInPack<T, Types...>();
	}


	template<class ...SearchedTypes>
	static constexpr bool containsTypes()
	{
		return (containsType<SearchedTypes>() && ...);
	}

	template<>
	static constexpr bool containsTypes<>()
	{
		return false;
	}


	template<class ...OtherTypes>
	struct AreUsed : public std::bool_constant<containsTypes<OtherTypes...>()>{};

};

#include "TuplePlus.inl"