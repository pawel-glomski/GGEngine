#include "Engine/Modules/Display/DisplayLayer.h"


void DisplayLayer::draw(const sf::Drawable & drawable, const sf::RenderStates & states)
{
	layerElemets.push_back(std::pair<const sf::Drawable&, sf::RenderStates>(drawable, states));
}

void DisplayLayer::display(sf::RenderTarget & target)
{
	for (auto & element : layerElemets)
		target.draw(element.first, element.second);

	layerElemets.clear();
}
