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

	window.draw(lines);
	for (auto& point : points)
		window.draw(point);

	window.display();

	points.clear();
	lines.clear();
}

void DisplayModule::drawWorldObject(const sf::Drawable & object, const Transform & transform, DisplayLayer::Level level)
{
	sf::RenderStates states;

	states.transform.translate(asVec<sf::Vector2f>(transform.position) * Settings<WindowModule>::WorldToViewRatio);
	states.transform.rotate(toDegrees(transform.rotation));
	states.transform.scale(asVec<sf::Vector2f>(transform.scale) * Settings<WindowModule>::WorldToViewRatio);

	layers[(uint8_t)level].draw(object, states);
}

void DisplayModule::drawWindowObject(const sf::Drawable & object, DisplayLayer::Level level)
{
	layers[(uint8_t)level].draw(object);
}

void DisplayModule::drawWorldPoint(Vec2f point, float size, sf::Color color)
{
	points.emplace_back(sf::Vector2f(size, size) * Settings<WindowModule>::WorldToViewRatio);
	points.back().setOrigin(points.back().getSize() / 2.f);
	points.back().setPosition(asVec<sf::Vector2f>(point) * Settings<WindowModule>::WorldToViewRatio);
	points.back().setFillColor(color);
}

void DisplayModule::drawWindowPoint(Vec2f point, float size, sf::Color color)
{
	points.emplace_back(sf::Vector2f(size, size));
	points.back().setOrigin(points.back().getSize() / 2.f);
	points.back().setPosition(asVec<sf::Vector2f>(point));
	points.back().setFillColor(color);
}

void DisplayModule::drawWorldLine(Vec2f start, Vec2f end, sf::Color color)
{
	lines.append(sf::Vertex(asVec<sf::Vector2f>(start) * Settings<WindowModule>::WorldToViewRatio, color));
	lines.append(sf::Vertex(asVec<sf::Vector2f>(end) * Settings<WindowModule>::WorldToViewRatio, color));
}

void DisplayModule::drawWindowLine(Vec2f start, Vec2f end, sf::Color color)
{
	lines.append(sf::Vertex(asVec<sf::Vector2f>(start), color));
	lines.append(sf::Vertex(asVec<sf::Vector2f>(end), color));
}
