#pragma once
#include <array>
#include "Engine/Modules/Window/WindowModule.h"
#include "Engine/Utility/Math/Transform.h"
#include "DisplayLayer.h"



class DisplayModule : public Module<WindowModule>
{
public:

	template<class ...MTypes>
	DisplayModule(const MDepPack_t<MTypes...> & dependencies);


	virtual void update() override;


	// when object's transform is in world coordinates
	void drawWorldObject(const sf::Drawable & object, const Transform & transform, DisplayLayer::Level level);

	// when object's transform is in window coordinates
	void drawWindowObject(const sf::Drawable & object, DisplayLayer::Level level);


	void drawWorldPoint(Vec2f point, float size, sf::Color = sf::Color::White);

	void drawWindowPoint(Vec2f point, float size, sf::Color = sf::Color::White);

	void drawWorldLine(Vec2f start, Vec2f end, sf::Color = sf::Color::White);

	void drawWindowLine(Vec2f start, Vec2f end, sf::Color = sf::Color::White);

private:

	void displayLayers();

private:

	std::array<DisplayLayer, (uint8_t)DisplayLayer::Level::Count> layers;

	std::vector<sf::RectangleShape> points;

	sf::VertexArray lines;

};
 


template<class ...MTypes>
inline DisplayModule::DisplayModule(const MDepPack_t<MTypes...>& dependencies) : ModuleBase_t(dependencies)
{
	lines.setPrimitiveType(sf::PrimitiveType::Lines);
}