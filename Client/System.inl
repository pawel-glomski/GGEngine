
template<class ...CTypes>
template<class ...Dependencies>
inline void System<CTypes...>::init(const TuplePlus<Dependencies...>& dep)
{
	// default init function
}

template<class ...CTypes>
inline void System<CTypes...>::removeEntity(EntityId id)
{
	ASSERT(entitiesComponents.count(id), "Tried to remove components of unidentified entity (probably entity is already destroyed)");
	if (entitiesComponents.count(id))
		entitiesComponents.erase(id);
}

template<class ...CTypes>
template<class ...EntityCTypes>
inline typename std::enable_if<TuplePlus<EntityCTypes...>::template areUsed<CTypes...>, void>::type
System<CTypes...>::addEntity(EntityId id, const TuplePlus<CPtr_t<EntityCTypes>...>& componentsHolder)
{
	ASSERT(!entitiesComponents.count(id), std::string("Added components of entity with id: \"") + std::to_string(id) + "\" more than once!");
	((std::get<CPtr_t<CTypes>>(entitiesComponents[id]) = std::get<CPtr_t<CTypes>>(componentsHolder)), ...);
}