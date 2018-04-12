#pragma once
#include <array>
#include "WindowModule.h"
#include "DisplayLayer.h"
#include "TransformComponent.h"

class DisplayModule : public Module<WindowModule>
{
public:

	template<class ...MTypes>
	DisplayModule(const MDepPack_t<MTypes...> & dependencies) : ModuleBase_t(dependencies) {};


	virtual void update(float_t dt) override;

	// when object's transform is in world coordinates
	void drawWorldObject(const sf::Drawable & object, const Transform & transform, DisplayLayer::Level level);

	// when object's transform is in window coordinates
	void drawWindowObject(const sf::Drawable & object, DisplayLayer::Level level);


	void setWatchedEntity(const CPtr_t<TransformComponent>& watchedEntityTransform);


private:


	void updateView();


	void displayLayers();


private:

	std::array<DisplayLayer, (uint8_t)DisplayLayer::Level::Count> layers;


	std::weak_ptr<TransformComponent> followingTransformC;

};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Settings

template<>
struct Settings<DisplayModule>
{

};