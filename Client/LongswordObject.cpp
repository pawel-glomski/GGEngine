#include "LongswordObject.h"

LongswordObject::LongswordObject()
{
	getComponent<DisplayComponent>().setShape(RectangleShape(Vec2f(1.5f, 0.1f)));
	getComponent<DisplayComponent>().setColor(sf::Color::Blue);
	getComponent<TransformComponent>().moveForward(0.25f); // changing origin
}
