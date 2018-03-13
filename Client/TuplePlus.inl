#include "TuplePlus.h"

template<class ...Types>
template<class U>
inline U & TuplePlus<Types...>::get()
{
	static_assert(isTypeInPack<U, Types...>(), "Tried to get wrong type from tuple!");
	return std::get<U>(*this);
}

template<class ...Types>
template<class U>
inline const U & TuplePlus<Types...>::get() const
{
	static_assert(isTypeInPack<U, Types...>(), "Tried to get wrong type from tuple!");
	return std::get<U>(*this);
}


template<class ...Types>
template<class ...OtherTypes>
inline TuplePlus<OtherTypes...> TuplePlus<Types...>::asTuple()
{
	static_assert(AreUsed<OtherTypes...>::value || !sizeof...(OtherTypes), "Tuple does not contain given sequence of types");
	return std::tuple<OtherTypes...>(get<OtherTypes>()...);
}


template<class ...Types>
template<class ...OtherTypes>
inline TuplePlus<OtherTypes...> TuplePlus<Types...>::asTuple() const
{
	static_assert(AreUsed<OtherTypes...>::value || !sizeof...(OtherTypes), "Tuple does not contain given sequence of types");
	return std::tuple<OtherTypes...>(get<OtherTypes>()...);
}


template<class ...Types>
template<class ...OtherTypes>
inline TuplePlus<OtherTypes&...> TuplePlus<Types...>::asRefTuple()
{
	static_assert(AreUsed<OtherTypes...>::value || !sizeof...(OtherTypes), "Tuple does not contain given sequence of types");
	return std::tuple<OtherTypes&...>(get<OtherTypes>()...);
}



template<class ...Types>
template<class ...OtherTypes>
inline TuplePlus<const OtherTypes&...> TuplePlus<Types...>::asRefTuple() const
{
	static_assert(AreUsed<OtherTypes...>::value || !sizeof...(OtherTypes), "Tuple does not contain given sequence of types");
	return std::tuple<const OtherTypes&...>(get<OtherTypes>()...);
}
