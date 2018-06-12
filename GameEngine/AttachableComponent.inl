
template<class T>
inline AttachableComponent<T>::~AttachableComponent()
{
	if (parent)
		parent->detach(shared_from_this());

	for (auto i = attached.begin(); i != attached.end(); )
		detach(i);

	attached.clear();
}

template<class T>
inline void AttachableComponent<T>::attach(const ERefPtr_t& toAttach)
{
	ASSERT(toAttach, "Cannot attach nullptr");
	ASSERT(!toAttach->parent, "Component is already attached");
	ASSERT(!attached.count(toAttach), "Component is already attached");

	if (toAttach)
		if (auto comp = toAttach->getComponent<T>(); comp && !comp->parent && !attached.count(toAttach))
		{
			attached.emplace(toAttach);
			comp->parent = shared_from_this();
		}
}

template<class T>
inline void AttachableComponent<T>::detach(const ERefPtr_t& toDetach)
{
	auto componentI = attached.find(toDetach);
	ASSERT((componentI != attached.end()), "Unidentified component");
	if (componentI != attached.end())
		detach(componentI);
}

template<class T>
inline void AttachableComponent<T>::detach(AttachedIterator_t& componentI)
{
	ASSERT(((*componentI)->parent == this), "This component is not parent to the one to detach");
	if ((*componentI)->parent == this)
		componentI = attached.erase(componentI);
}

template<class T>
inline bool AttachableComponent<T>::isAttached() const
{
	return getParent();
}

template<class T>
inline const typename AttachableComponent<T>::ERefPtr_t & AttachableComponent<T>::getParent() const
{
	return parent;
}

template<class T>
inline T& AttachableComponent<T>::getTopParent()
{
	if (parent)
		return parent->getTopParent();
	return *(T*)this;
}

template<class T>
inline const T& AttachableComponent<T>::getTopParent() const
{
	if (parent)
		return parent->getTopParent();
	return *(T*)this;
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