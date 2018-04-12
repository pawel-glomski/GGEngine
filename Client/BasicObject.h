#pragma once
#include "Entity.h"
#include "ConstructableComponent.h"

// every object must own identity component, so they can be distinguished from others
template<class ...CTypes>
class BasicObject : public Entity<IdentityComponent, CTypes...>
{
protected:

	using ObjectBase_t = BasicObject<CTypes...>;

public:

	virtual void construct(ObjectModule& objectModule) override
	{
		(tryConstruct(getComponent<CTypes>(), objectModule), ...);
	}
	
private:


	void tryConstruct(ConstructableComponent & component, ObjectModule& objectModule)
	{
		component.construct(objectModule);
	}

	void tryConstruct(Component&, ObjectModule&) {}
};
