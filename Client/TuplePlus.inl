
template<class ...TplTypes>
template<class U>
inline U& TuplePlus<TplTypes...>::get()
{
	static_assert(isTypeInPack<U, TplTypes...>(), "Tried to get wrong type from tuple!");
	return std::get<U>(*this);
}

template<class ...TplTypes>
template<class U>
inline const U& TuplePlus<TplTypes...>::get() const
{
	static_assert(isTypeInPack<U, TplTypes...>(), "Tried to get wrong type from tuple!");
	return std::get<U>(*this);
}

template<class ...TplTypes>
template<class ...OtherTypes>
inline TuplePlus<OtherTypes...> TuplePlus<TplTypes...>::asTuple()
{
	static_assert(AreUsed<OtherTypes...>::value || !sizeof...(OtherTypes), "Tuple does not contain given sequence of types");
	return std::tuple<OtherTypes...>(get<OtherTypes>()...);
}


template<class ...TplTypes>
template<class ...OtherTypes>
inline TuplePlus<OtherTypes...> TuplePlus<TplTypes...>::asTuple() const
{
	static_assert(AreUsed<OtherTypes...>::value || !sizeof...(OtherTypes), "Tuple does not contain given sequence of types");
	return std::tuple<OtherTypes...>(get<OtherTypes>()...);
}



template<class ...TplTypes>
inline TuplePlus<TplTypes&...> TuplePlus<TplTypes...>::asRefTuple()
{
	return std::tuple<TplTypes&...>(get<TplTypes>()...);
}


template<class ...TplTypes>
inline TuplePlus<const TplTypes&...> TuplePlus<TplTypes...>::asRefTuple() const
{
	return std::tuple<const TplTypes&...>(get<TplTypes>()...);
}



template<class ...TplTypes>
template<class ...OtherTypes>
inline TuplePlus<OtherTypes&...> TuplePlus<TplTypes...>::asRefTuple()
{
	static_assert(AreUsed<OtherTypes...>::value || !sizeof...(OtherTypes), "Tuple does not contain given sequence of types");
	return std::tuple<OtherTypes&...>(get<OtherTypes>()...);
}


template<class ...TplTypes>
template<class ...OtherTypes>
inline TuplePlus<const OtherTypes&...> TuplePlus<TplTypes...>::asRefTuple() const
{
	static_assert(AreUsed<OtherTypes...>::value || !sizeof...(OtherTypes), "Tuple does not contain given sequence of types");
	return std::tuple<const OtherTypes&...>(get<OtherTypes>()...);
}
