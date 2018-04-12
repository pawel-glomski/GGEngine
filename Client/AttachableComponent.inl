
template<class T>
inline void AttachableComponent<T>::attach(const UsedCPtr_t& toAttach)
{
	ASSERT(toAttach, "Cannot attach nullptr");
	ASSERT(!toAttach->parent, "Component is already attached");
	ASSERT(!attached.count(toAttach), "Component is already attached");

	if (toAttach && !toAttach->parent && !attached.count(toAttach))
	{
		attached.emplace(toAttach);
		toAttach->parent = shared_from_this();
	}
}

template<class T>
inline void AttachableComponent<T>::detach(const UsedCPtr_t& toDetach)
{
	auto componentI = attached.find(toDetach);
	ASSERT((componentI != attached.end()), "Unidentified component");
	if (componentI != attached.end())
		detach(componentI);
}

template<class T>
inline void AttachableComponent<T>::detach(AttachedIterator_t& componentI)
{
	ASSERT(((*componentI)->parent == shared_from_this()), "This component is not parent to the one to detach");
	if ((*componentI)->parent == shared_from_this())
	{
		(*componentI)->parent.reset();
		componentI = attached.erase(componentI);
	}
}

template<class T>
inline void AttachableComponent<T>::onDestroy()
{
	if (parent)
		parent->detach(shared_from_this());

	for (auto i = attached.begin(); i != attached.end(); )
		detach(i);

	attached.clear();
}

template<class T>
inline bool AttachableComponent<T>::isAttached() const
{
	return bool(getParent());
}

template<class T>
inline const typename AttachableComponent<T>::UsedCPtr_t& AttachableComponent<T>::getParent() const
{
	return parent;
}

template<class T>
inline typename AttachableComponent<T>::AttachedContainer_t & AttachableComponent<T>::getAttached()
{
	return attached;
}

template<class T>
inline const typename AttachableComponent<T>::AttachedContainer_t & AttachableComponent<T>::getAttached() const
{
	return attached;
}


// utilities


template<class ...CTypes, class T>
inline typename std::enable_if<CPack_t<CTypes...>::template AreUsed<CPtr_t<T>>::value>::type
tryAttach(const CPack_t<CTypes...>& parentPack, AttachableComponent<T>& toAttach)
{
	parentPack.get<CPtr_t<T>>()->attach(toAttach.shared_from_this());
}

template<class ...CTypes>
inline void tryAttach(const CPack_t<CTypes...>& parentPack, Component&) {}


template<class ParentCPack, class ...ChildCTypes>
inline void attachAllComponents(const ParentCPack& parentPack, const CPack_t<ChildCTypes...>& childPack)
{
	(tryAttach(parentPack, *childPack.get<CPtr_t<ChildCTypes>>()), ...);
}