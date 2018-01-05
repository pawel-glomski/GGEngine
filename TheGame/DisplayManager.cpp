#include "stdInclude.h"
#include "DisplayManager.h"


DisplayManager::DisplayManager(const GraphicsSettings & settings)
{
	createWindow(settings);
}

sf::RenderWindow & DisplayManager::createWindow(const GraphicsSettings & settings)
{
	sf::VideoMode vidMode;
	vidMode.width = GraphicsSettings::resolutions[uint8_t(settings.resolution)].x;
	vidMode.height = GraphicsSettings::resolutions[uint8_t(settings.resolution)].y;
	window.create(vidMode, "TheGame", settings.windowType, sf::ContextSettings(0, 0, settings.antialiasting));

	return window;
}

sf::RenderWindow& DisplayManager::getWin()
{
	return window;
}

const sf::RenderWindow & DisplayManager::getWin() const
{
	return window;
}


bool DisplayManager::isWinOpen() const
{
	return window.isOpen();
}

void DisplayManager::operator()(const World & world)
{
	window.clear();
	//... draw world's elements
	window.display();
}