#pragma once
#include <SFML/Graphics.hpp>
#include "World.h"
#include "Singleton.h"

struct GraphicsSettings
{
	enum class Resolution : uint8_t
	{
		R1280x720,
		RCount
	};

	Resolution	resolution = Resolution(0);
	uint32_t	windowType = 7U;
	uint32_t	antialiasting = 0U;

	static const sf::Vector2u resolutions[uint8_t(Resolution::RCount)]; // "resolution" variable can be used as an index in this array
};

class DisplayManager
{
public:

	void startUp(const GraphicsSettings & settings = GraphicsSettings());
	void shoutDown();

	const std::shared_ptr<sf::RenderWindow> & createWindow(const GraphicsSettings& settings = GraphicsSettings()) const;
	const std::shared_ptr<sf::RenderWindow> & getWin() const;

	void display(const World & world);

private:
	std::shared_ptr<sf::RenderWindow> window;
};

