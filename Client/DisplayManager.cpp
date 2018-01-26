#include "stdInclude.h"
#include "DisplayManager.h"

const sf::Vector2u GraphicsSettings::resolutions[uint8_t(Resolution::RCount)] =
{
	{ 1280, 720 }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DisplayManager::startUp(const GraphicsSettings & settings)
{
	window = std::make_shared<sf::RenderWindow>();
	createWindow();
}

void DisplayManager::shoutDown()
{
	ASSERT(window.unique(), "DisplayManager shoutdown while there are pointers pointing to window");
	window->close();
}

const std::shared_ptr<sf::RenderWindow>& DisplayManager::createWindow(const GraphicsSettings & settings) const
{
	sf::VideoMode vidMode;
	vidMode.width = GraphicsSettings::resolutions[uint8_t(settings.resolution)].x;
	vidMode.height = GraphicsSettings::resolutions[uint8_t(settings.resolution)].y;
	window->create(vidMode, "TheGame", settings.windowType, sf::ContextSettings(0, 0, settings.antialiasting));
	window->setKeyRepeatEnabled(false);


	window->setFramerateLimit(60);
	ASSERT(false, "Window FPS is set to 60");
	return window;
}

const std::shared_ptr<sf::RenderWindow>& DisplayManager::getWin() const
{
	return window;
}

void DisplayManager::display(const World & world)
{
	window->clear();
	world.display(*window);
	window->display();
}