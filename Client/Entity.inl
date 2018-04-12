#include "Entity.h"

template<class ...CTypes>
inline Entity<CTypes...>::Entity() : components(std::make_tuple(std::make_shared<CTypes>()...))
{}

template<class ...CTypes>
inline const typename Entity<CTypes...>::UsedCPack_t& Entity<CTypes...>::getComponents() const
{
	return components;
}

template<class ...CTypes>
inline typename Entity<CTypes...>::UsedCRefPack_t Entity<CTypes...>::getComponentsRefPack() const
{
	return TypesPack_t<CTypes&...>(typename TypesPack_t<CTypes&...>::Base_t(getComponent<CTypes>()...));
}

template<class ...CTypes>
template<class T>
inline T& Entity<CTypes...>::getComponent() const
{
	return *components.get<CPtr_t<T>>();
}

template<class ...CTypes>
template<class T>
inline const CPtr_t<T>& Entity<CTypes...>::getComponentPtr() const
{
	return components.get<CPtr_t<T>>();;
}

template<class ...CTypes>
template<class T>
inline void Entity<CTypes...>::assertOneReference()
{
	ASSERT((getComponentPtr<T>().use_count() == 1), std::string("Component is referenced outside of entity on its destruction. Component name: ") + std::type_index(typeid(T)).name()
	+ " Entity Id: " + std::to_string(getComponent<IdentityComponent>().getId()) + " References count : " + std::to_string(getComponentPtr<T>().use_count()));
}