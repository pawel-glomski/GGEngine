#pragma once
#include <tuple>

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



	template<class T>
	static constexpr bool containsType();


	template<class ...SearchedTypes>
	static constexpr bool containsTypes();


	template<>
	static constexpr bool containsTypes<>();


	template<class ...OtherTypes>
	TuplePlus<OtherTypes...> asTuple() const;


	template<class ...OtherTypes>
	static constexpr bool areUsed = containsTypes<OtherTypes...>();

};

#include "TuplePlus.inl"