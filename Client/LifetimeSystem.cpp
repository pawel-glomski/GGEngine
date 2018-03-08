#include "LifetimeSystem.h"
#include "EntityManager.h"

LifetimeSystem::LifetimeSystem()
{
	usesEveryEntity = false;
}

void LifetimeSystem::update(EntityManager & entityManager, float_t dt)
{
	// entities are always destroyed in right order:
	// when entity is destoyed, then it is destroyed before entities attached to it, so that it unattach them in RelationComponent destructor
	// this means, that when entity with parent is destroyed independently, parent and its components are for sure valid, couse entity is still attached to that entity

	if (entitiesToUpdate)
		for (auto & entityNode : *entitiesToUpdate)
		{
			auto & entity = *entityNode.second;
			auto lifetimeComponent = entity.getComponent<LifetimeComponent>();

			if (!lifetimeComponent->wasSpawned())
				lifetimeComponent->spawn();
			else if (lifetimeComponent->isDying())
			{
				// destroy this entity first
				entityManager.destroyTempEntity(entity.getID());
				lifetimeComponent->destroy();

				// then destroy also attached entities

				for (auto & attached : entity.getComponent<RelationComponent>()->getAttached())
				{
					auto & attEntity = attached.second;
					attEntity->getComponent<LifetimeComponent>()->die();
					entityManager.destroyTempEntity(attached.second->getID());
					attEntity->getComponent<LifetimeComponent>()->destroy();
				}
			}
		}
}

void LifetimeSystem::addEntity(const EntityManager::EntityPtr & entity, const std::shared_ptr<EntityManager::EntityContainer>& everyEntityContainer)
{
	if (entity->getComponent<LifetimeComponent>()->getLifeTime() == Lifetime::Temp)
		EntityUpdateSystem::addEntity(entity, everyEntityContainer);
}
