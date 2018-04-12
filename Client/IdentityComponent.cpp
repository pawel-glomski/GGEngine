#include "IdentityComponent.h"


void IdentityComponent::createIdentity(IdScope scope, Lifetime lifetime)
{
	ASSERT(!hasIdentity(), "Identity can be created only once per IdentityComponent");
	if (id == UnidentifiedID)
	{
		id = newId(scope);
		this->idScope = scope;
		this->lifetime = lifetime;
	}
}

EntityId IdentityComponent::getId() const
{
	ASSERT(hasIdentity(), "Returned unidentified id");
	return id;
}

IdScope IdentityComponent::getIdScope() const
{
	return idScope;
}

Lifetime IdentityComponent::getLifetime() const
{
	return lifetime;
}

bool IdentityComponent::hasIdentity() const
{
	return isIdIdentified(id);
}

bool IdentityComponent::isIdIdentified(EntityId id)
{
	return (id != UnidentifiedID);
}

EntityId IdentityComponent::newId(IdScope scope)
{
	static EntityId globalScopeCounter = UnidentifiedID + 1;
	static EntityId localScopeCounter = std::numeric_limits<EntityId>().max() / 2;

	if (scope == IdScope::Global)
		return globalScopeCounter++;
	if (scope == IdScope::Local)
		return localScopeCounter++;

	ASSERT((scope != IdScope::None), "Tried to get new id of None Scope, returned unidentified id");
	return UnidentifiedID;
}