
template<class ...Types>
inline Entity<Types...>::Entity(EntityId id) : id(id), components(std::make_tuple(std::make_shared<Types>()...)) {}

template<class ...Types>
inline EntityId Entity<Types...>::getId() const
{
	return id;
}

template<class ...Types>
inline typename Entity<Types...>::CHolder_t & Entity<Types...>::getComponents()
{
	return components;
}

template<class ...Types>
inline const typename Entity<Types...>::CHolder_t & Entity<Types...>::getComponents() const
{
	return components;
}

template<class ...Types>
template<class T>
inline Entity<Types...>::CPtr_t<T>& Entity<Types...>::getComponent()
{
	static_assert(isTypeInPack<T, Types...>(), "Tried to get component of wrong Type from an entity");
	return std::get<CPtr_t<T>>(components);
}

template<class ...Types>
template<class T>
inline const Entity<Types...>::CPtr_t<T> & Entity<Types...>::getComponent() const
{
	static_assert(isTypeInPack<T, Types...>(), "Tried to get component of wrong Type from an entity");
	return std::get<CPtr_t<T>>(components);
}
