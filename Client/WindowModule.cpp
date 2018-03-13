#include "WindowModule.h"

sf::RenderWindow & WindowModule::getWin()
{
	return window;
}

const sf::RenderWindow & WindowModule::getWin() const
{
	return window;
}
