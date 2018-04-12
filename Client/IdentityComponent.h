#pragma once
#include "MathUtilities.h"
#include "AttachableComponent.h"

using EntityId = uint32_t;

inline const uint32_t UnidentifiedID = 0;


enum class IdScope { None, Global, Local };

// Describes lifetime of an entity owning IdentityComponent
// When attached, it describes lifetime local to parent's, and its global lifetime is always same as parent's.
// This means, that when set to Perm, to parent that entity cannot be destroyed (hence it will always be valid), 
// but from the global perspective, attached entity's lifetime is always same as parent's global lifetime
enum class Lifetime : uint8_t
{
	None,
	Temp,	// can be directly destroyed
	Perm	// protects entity from direct destruction 
};



// Attachment effects - attached entity shares lifetime with parent.
class IdentityComponent : public AttachableComponent<IdentityComponent>
{
public:

	IdentityComponent() = default;

	IdentityComponent(const IdentityComponent &) = delete;

	IdentityComponent(IdentityComponent &&) = default;

	IdentityComponent& operator=(IdentityComponent&&) = default;



	void createIdentity(IdScope scope, Lifetime lifetime);


	bool hasIdentity() const;


	EntityId getId() const;

	IdScope getIdScope() const;

	Lifetime getLifetime() const;


	static EntityId newId(IdScope scope);

	// returns true if id is not UnidentifiedID, does not check if entity still exists/ is valid
	static bool isIdIdentified(EntityId id);


private:

	EntityId id = UnidentifiedID;

	IdScope idScope = IdScope::None;

	Lifetime lifetime = Lifetime::None;
};