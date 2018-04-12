#pragma once
#include <tuple>
#include "stdInclude.h"

template<class T, class ...Pack>
inline constexpr bool isTypeInPack()
{
	return (std::is_same_v<T, Pack> || ...);
}

template<class T>
inline T tupleTestElement;




template<class ...TplTypes>
struct TuplePlus : public std::tuple<TplTypes...>
{
	using ThisTpl_t = TuplePlus<TplTypes...>;

	using Base_t = std::tuple<TplTypes...>;


	using Decayed_t = TuplePlus<std::decay_t<TplTypes>...>;

	
	template< template <typename T> class TemplateType>
	using WithElementsWrappedInTemplate_t = TuplePlus< TemplateType<TplTypes>...>;




	TuplePlus() = default;

	TuplePlus(const ThisTpl_t&) = default;

	TuplePlus(const Base_t& rhs) : Base_t(rhs) {}


	template<class U>
	U& get();

	template<class U>
	const U& get() const;


	template<class ...OtherTypes>
	TuplePlus<OtherTypes...> asTuple();

	template<class ...OtherTypes>
	TuplePlus<OtherTypes...> asTuple() const;


	TuplePlus<TplTypes&...> asRefTuple();

	TuplePlus<const TplTypes&...> asRefTuple() const;


	template<class ...OtherTypes>
	TuplePlus<OtherTypes&...> asRefTuple();

	template<class ...OtherTypes>
	TuplePlus<const OtherTypes&...> asRefTuple() const;


	template<class ...OtherTplTypes>
	static ThisTpl_t makeFromTuple(const TuplePlus<OtherTplTypes...>& tplToCpyFrom)
	{
		return ThisTpl_t(Base_t(tplToCpyFrom.get<TplTypes>()...));
	}

	static ThisTpl_t& getTestInstance()
	{
		static ThisTpl_t testInstance = ThisTpl_t(Base_t(tupleTestElement<std::decay_t<TplTypes>>...));
		return testInstance;
	}


	template<class T>
	static constexpr bool containsType()
	{
		return isTypeInPack<T, TplTypes...>();
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
	struct AreUsed : public std::bool_constant<containsTypes<OtherTypes...>()> {};

};


template<class ...TplTypes>
using TypesPack_t = TuplePlus<TplTypes...>;

#include "TuplePlus.inl"