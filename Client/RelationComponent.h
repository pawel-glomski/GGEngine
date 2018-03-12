#pragma once
#include <memory>
#include <unordered_map>
#include "Component.h"
#include "Entity.h"

// handles parent-child entities' relations with transform binding, that resets relations on destroyment
class RelationComponent :
	public Component
{
public:

	RelationComponent() = default;

	RelationComponent(const RelationComponent &) = delete;

	~RelationComponent();

	void setOwningEntity(const std::shared_ptr<Entity> & owner);

	void attachTo(const std::shared_ptr<Entity> & parent);

	void unattachSelf();


	const std::shared_ptr<Entity> & getParent();

	const std::unordered_map<std::size_t, std::shared_ptr<Entity>> & getAttached() const;

private:

	void removeReferencesToParent();

private:

	std::shared_ptr<Entity> owner; // entity that owns this component

	std::shared_ptr<Entity> parent;

	std::unordered_map<std::size_t, std::shared_ptr<Entity>> attached;
};

