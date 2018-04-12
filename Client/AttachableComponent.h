#pragma once
#include <unordered_set>
#include "Component.h"

template<class T>
class AttachableComponent : 
	public Component,
	public std::enable_shared_from_this<T>
{

protected:

	using AttCompBase_t = AttachableComponent<T>;


	using UsedCPtr_t = CPtr_t<T>;

	using AttachedContainer_t = std::unordered_set<UsedCPtr_t>;

	using AttachedIterator_t = typename AttachedContainer_t::iterator;
	
public:

	virtual void attach(const UsedCPtr_t& toAttach);

	virtual void detach(const UsedCPtr_t& toDetach);


	virtual void onDestroy() override;


	bool isAttached() const;


	const UsedCPtr_t& getParent() const;

	AttachedContainer_t& getAttached();

	const AttachedContainer_t& getAttached() const;


private:

	void detach(AttachedIterator_t & componentI);


protected:

	UsedCPtr_t parent;

	AttachedContainer_t attached;
};

#include "AttachableComponent.inl"