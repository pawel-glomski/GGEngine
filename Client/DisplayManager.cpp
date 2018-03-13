#include "stdInclude.h"
#include "DisplayManager.h"
#include "TransformComponent.h"


const sf::Vector2u DisplaySettings::windowSizes[uint8_t(WindowSize::SCount)] =
{
	{ 1280, 720 }, { 1920, 1080 }
};

const Vec2f DisplaySettings::ViewResolution = Vec2f(1920, 1080);

const float_t DisplaySettings::WorldToWindowRatio = 100.f;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DisplayManager::startUp(const DisplaySettings & settings)
{
	window = std::make_shared<sf::RenderWindow>();
	createWindow();
}

void DisplayManager::shoutDown()
{
	ASSERT((window.use_count() == 1), "DisplayManager shoutdown while there are pointers pointing to window");
	window->close();
	window.reset();
}

const std::shared_ptr<sf::RenderWindow>& DisplayManager::createWindow(const DisplaySettings & settings)
{
	this->settings = settings;
	sf::VideoMode vidMode;
	vidMode.width = DisplaySettings::windowSizes[uint8_t(settings.windowSize)].x;
	vidMode.height = DisplaySettings::windowSizes[uint8_t(settings.windowSize)].y;
	window->create(vidMode, "TheGame", settings.windowType, sf::ContextSettings(0, 0, settings.antialiasting));
	window->setView(sf::View(sf::Vector2f(0,0), sf::Vector2f(DisplaySettings::ViewResolution.asSfVec())));
	window->setKeyRepeatEnabled(false);


	//window->setFramerateLimit(120);
	//ASSERT(false, "Window FPS is set to 120");
	return window;
}

const std::shared_ptr<sf::RenderWindow>& DisplayManager::getWin() const
{
	return window;
}

void DisplayManager::display(const std::shared_ptr<DisplaySystem> system)
{
	//window->clear();
	//for (auto & layer : system->displayLayers)
	//	layer.display(*window);

	//for (auto & gridCell : system->entityGrid)
	//{
	//	sf::RectangleShape grid(sf::Vector2f(system->gridSize, system->gridSize) * DisplaySettings::WorldToWindowRatio);
	//	grid.setFillColor(sf::Color::Transparent);
	//	grid.setOutlineThickness(5);
	//	auto cellPositon = gridCell.first;
	//	if (cellPositon.x > 0)
	//		cellPositon.x--;
	//	if (cellPositon.y > 0)
	//		cellPositon.y--;
	//	cellPositon *= (int32_t)DisplaySettings::WorldToWindowRatio;
	//	grid.setPosition(cellPositon.x * system->gridSize, cellPositon.y * system->gridSize);
	//	auto camPos = system->camera.lock()->getComponent<TransformComponent>()->getGlobalPosition();
	//	camPos += Vec2f(sign(camPos.x), sign(camPos.y)) * system->gridSize;
	//	camPos /= system->gridSize;
	//	if (Vec2i(camPos) == gridCell.first)
	//		grid.setOutlineColor(sf::Color::White);
	//	else
	//		grid.setOutlineColor(sf::Color::Red);
	//	window->draw(grid);
	//}
	//sf::RectangleShape windowView(sf::Vector2f(DisplaySettings::ViewResolution.asSfVec()));
	//windowView.setPosition(window->getView().getCenter() - sf::Vector2f((DisplaySettings::ViewResolution / 2.f).asSfVec()));
	//windowView.setFillColor(sf::Color::Transparent);
	//windowView.setOutlineThickness(5);
	//windowView.setOutlineColor(sf::Color::Green);
	//window->draw(windowView);

	window->display();
}