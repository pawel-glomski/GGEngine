#pragma once
#include <memory>
#include <unordered_map>
#include "EntityUpdateSystem.h"
#include "DisplayComponent.h"
#include "DisplayManager.h"
#include "EntityManager.h"
#include "DisplayLayer.h"
#include "Camera.h"


class DisplaySystem :
	public EntityUpdateSystem
{
	friend class DisplayManager;
public:

	DisplaySystem();

	void startUp(const std::shared_ptr<DisplayManager> & displayManager);
	
	void shoutDown();


	virtual void update(EntityManager & entityManager, float_t dt) override;


	virtual void addEntity(const EntityManager::EntityPtr & entity, const std::shared_ptr<EntityManager::EntityContainer> & everyEntityContainer) override;

	virtual void removeEntity(const Entity::ID & entity);

	virtual void reset();


	void setCamera(const std::shared_ptr<Entity> & camera);

private:

	virtual void beforeUpdate();


	void drawWorldStaticEntities();

	void drawDynamicEntities();

	void drawEntity(const Entity & entity);


private:

	std::unordered_map<Vec2i, std::unordered_map<Entity::ID, EntityManager::EntityPtr>, Vec2Hash<int32_t>> entityGrid;

	const float_t gridSize = 2;

	// level-divided entities to draw in DisplayManager
	// DisplayLevel members are used as indices here
	std::array<DisplayLayer, (uint8_t)DisplayLayer::Level::Count> displayLayers;

	std::shared_ptr<DisplayManager> displayManager;

	std::weak_ptr<Camera> camera;
};