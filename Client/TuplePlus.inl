
template<class ...Types>
template<class T>
inline constexpr bool TuplePlus<Types...>::containsType()
{
	return isTypeInPack<T, Types...>();
}

template<class ...Types>
template<class ...SearchedTypes>
inline constexpr bool TuplePlus<Types...>::containsTypes()
{
	return (containsType<SearchedTypes>() && ...);
}

template<class ...Types>
template<class ...OtherTypes>
inline TuplePlus<OtherTypes...> TuplePlus<Types...>::asTuple() const
{
	static_assert(areUsed<OtherTypes...>, "Tuple does not contain given sequence of types");
	return std::make_tuple(std::get<OtherTypes>(*this)...);
}

template<>
template<class ...SearchedTypes>
inline constexpr bool TuplePlus<>::containsTypes()
{
	return false;
}