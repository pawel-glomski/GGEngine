#pragma once
#include <SFML/Graphics.hpp>
#include "SettingsManager.h"
#include "World.h"

class DisplayManager
{
public:
	DisplayManager() = default;
	DisplayManager(const GraphicsSettings& settings);

	sf::RenderWindow&		createWindow(const GraphicsSettings& settings = GraphicsSettings());
	sf::RenderWindow&		getWin();
	const sf::RenderWindow&	getWin() const;
	bool					isWinOpen() const;

	void operator()(const World & world);

private:
	sf::RenderWindow window;
};

