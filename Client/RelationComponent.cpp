#include "RelationComponent.h"
#include "stdInclude.h"
#include "Entity.h"
#include "TransformComponent.h"

RelationComponent::~RelationComponent()
{
//	if(parent)
//		unattachSelf();
//	// remove all references from attached entities, to this entity
//	for (auto &entityPtr : attached)
//		entityPtr.second->getComponent<RelationComponent>()->removeReferencesToParent();
}

void RelationComponent::setOwningEntity(const std::shared_ptr<Entity>& owner)
{
	ASSERT(!this->owner, "Tried to set owning entity, while its already set. Owner can be set only once!");
	if(!this->owner)
		this->owner = owner;
}

void RelationComponent::attachTo(const std::shared_ptr<Entity>& parent)
{
	//ASSERT(parent, "Tried to attach entity to nullptr");
	//ASSERT(!this->parent, "Tried to attach already attached entity. To reattach entity to other, unattach it first");
	//ASSERT((parent != owner), "Tried to attach entity to itself");
	//if (parent && !this->parent && parent != owner)
	//{
	//	this->parent = parent;
	//	parent->getComponent<RelationComponent>()->attached[owner->getID()] = owner;
	//	owner->getComponent<TransformComponent>()->setParentTransform(parent->getComponent<TransformComponent>());
	//}
}

void RelationComponent::unattachSelf()
{
	//ASSERT(parent, "Tried to unattach unattached entity");
	//if (parent)
	//{
	//	auto parentRelationComp = parent->getComponent<RelationComponent>();
	//	Entity::ID id = owner->getID();

	//	ASSERT(parentRelationComp->attached.count(id), "Tried to unattach entity from parent, that it is not attached to");
	//	if (parentRelationComp->attached.count(id))
	//	{
	//		parentRelationComp->attached.erase(id);
	//		removeReferencesToParent();
	//	}
	//}
}

const std::shared_ptr<Entity>& RelationComponent::getParent()
{
	return parent;
}

const std::unordered_map<std::size_t, std::shared_ptr<Entity>>& RelationComponent::getAttached() const
{
	return attached;
}

void RelationComponent::removeReferencesToParent()
{
	//owner->getComponent<TransformComponent>()->resetParentTransform();
	parent.reset();
}

