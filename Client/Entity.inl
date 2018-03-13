
template<class ...Types>
inline Entity<Types...>::Entity(EntityId id) : EntityBase(id), components(std::make_tuple(std::make_shared<Types>()...)) {}


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
	return components.get<CPtr_t<T>>();
}

template<class ...Types>
template<class T>
inline const Entity<Types...>::CPtr_t<T> & Entity<Types...>::getComponent() const
{
	return components.get<CPtr_t<T>>();
}
