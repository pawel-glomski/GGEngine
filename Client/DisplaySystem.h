#pragma once
#include <memory>
#include <unordered_set>
#include "System.h"
#include "DisplayComponent.h"
#include "TransformComponent.h"
#include "DisplayLayer.h"
#include "Camera.h"


class DisplaySystem :
	public System<DisplayComponent, TransformComponent>
{
	friend class DisplayManager;
public:

	DisplaySystem();

	void startUp(const std::shared_ptr<DisplayManager> & displayManager);
	
	void shoutDown();


	virtual void update(float_t dt) override;

private:

	void drawWorldStaticEntities();

	void drawDynamicEntities();

	void drawEntity(EntityId id);


private:

	std::unordered_map<Vec2i, std::unordered_set<EntityId>, Vec2Hash<int32_t>> entityGrid;

	const float_t gridSize = 2;

	// Layer-divided entities to draw in DisplayManager
	// DisplayLevel members are used as indices here
	std::array<DisplayLayer, (uint8_t)DisplayLayer::Level::Count> displayLayers;
};