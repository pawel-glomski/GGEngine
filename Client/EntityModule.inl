
template<class ...EntityTypes>
template<class T, class ...Args_t>
inline const EntityModule<EntityTypes...>::EPtr_t<T>& EntityModule<EntityTypes...>::spawnEntity(Args_t && ...args)
{
	static_assert(isTypeInPack<T, EntityTypes...>(), "Wrong Entity type. Only types set in EntityManager's declaration can be spawned by it");

	EContainer_t<T> & container = std::get<EContainer_t<T>>(entitiesContainers);
	EPtr_t<T> entity = std::make_unique<T>(++idCounter, std::forward<Args_t>(args)...);
	systems.addEntity(entity);
	entity->construct(*this);

	return container[entity->getId()] = std::move(entity);
}

template<class ...EntityTypes>
template<class T>
inline void EntityModule<EntityTypes...>::destroyEntity(const EPtr_t<T>& entity)
{
	destroyEntity<T>(entity->getId());
}

template<class ...EntityTypes>
template<class T>
inline void EntityModule<EntityTypes...>::destroyEntity(EntityId id)
{
	systems.removeEntity(id);
	std::get<EContainer_t<T>>(entitiesContainers).erase(id);
}

template<class ...EntityTypes>
inline void EntityModule<EntityTypes...>::update(float_t dt)
{
	systems.update(dt);
}