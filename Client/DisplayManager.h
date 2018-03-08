#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Camera.h"
#include "EntityManager.h"

struct DisplaySettings
{
	enum class WindowSize : uint8_t
	{
		S1280x720, S1920x1080,
		SCount
	};


	WindowSize	windowSize = WindowSize::S1280x720;

	uint32_t	windowType = sf::Style::Close;

	uint32_t	antialiasting = 0U;


	static const sf::Vector2u windowSizes[uint8_t(WindowSize::SCount)]; // "resolution" variable can be used as an index in this array

	static const Vec2f ViewResolution;

	static const float_t WorldToWindowRatio;
};

class DisplayManager
{
public:

	void startUp(const DisplaySettings & settings = DisplaySettings());

	void shoutDown();


	const std::shared_ptr<sf::RenderWindow> & createWindow(const DisplaySettings& settings = DisplaySettings());

	const std::shared_ptr<sf::RenderWindow> & getWin() const;


	void display(const std::shared_ptr<class DisplaySystem> system);


private:

	DisplaySettings settings;

	std::shared_ptr<sf::RenderWindow> window;
};