#include "DisplayModule.h"

void DisplayModule::update()
{
	displayLayers();
}

void DisplayModule::displayLayers()
{
	auto & window = getDependency<WindowModule>().getWin();

	window.clear();

	for (auto & layer : layers)
		layer.display(window);

	window.display();
}

void DisplayModule::drawWorldObject(const sf::Drawable & object, const Transform & transform, DisplayLayer::Level level)
{
	sf::RenderStates states;

	states.transform.translate(asVec<sf::Vector2f>(transform.position) * Settings<WindowModule>::WorldToViewRatio);
	states.transform.rotate(toDegrees(transform.rotation));
	states.transform.scale(asVec<sf::Vector2f>(transform.scaleV) * Settings<WindowModule>::WorldToViewRatio);

	layers[(uint8_t)level].draw(object, states);
}

void DisplayModule::drawWindowObject(const sf::Drawable & object, DisplayLayer::Level level)
{
	layers[(uint8_t)level].draw(object);
}