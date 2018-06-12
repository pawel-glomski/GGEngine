#pragma once
#include <SFML/Graphics.hpp>
#include "Module.h"
#include "MathUtilities.h"
#include "Clock.h"
#include "Settings.h"


class WindowModule : public Module<>
{
public:

	using Settings_t = Settings<WindowModule>;

public:

	template<class ...MTypes>
	WindowModule(const MDepPack_t<MTypes...> & dependencies) : ModuleBase_t(dependencies) {};


	virtual void startUp() override;

	virtual void update() override
	{
		window.setTitle(std::to_string(1.f / SimulationClock::getDeltaTime()));
	}


	sf::RenderWindow & getWin();

	const sf::RenderWindow & getWin() const;


	// returns ViewResolution scale to current window size
	Vec2f getRatioToMatchDefaultResolution() const;


private:

	sf::RenderWindow window;

};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Settings


template<>
struct Settings<WindowModule>
{
	enum class WindowSize : uint8_t
	{
		S1280x720, S1920x1080,
		SCount
	};


	// creates window using current settings
	void makeWindow(sf::RenderWindow& window);



	WindowSize	windowSize = WindowSize::S1280x720;

	uint32_t	windowType = sf::Style::Close;

	uint32_t	antialiasingLevel = 8;


	static const sf::Vector2u windowSizes[uint8_t(WindowSize::SCount)]; // "resolution" variable can be used as an index in this array

	static const Vec2f ViewResolution;

	static const float_t WorldToViewRatio;
};


inline void Settings<WindowModule>::makeWindow(sf::RenderWindow & window)
{
	sf::VideoMode videoMode;
	sf::View view;
	sf::ContextSettings settings;

	videoMode.width = windowSizes[(uint8_t)windowSize].x;
	videoMode.height = windowSizes[(uint8_t)windowSize].y;
	settings.antialiasingLevel = antialiasingLevel;

	window.create(videoMode, "TheGame", windowType, settings);

	view = window.getView();
	view.setSize(asVec<sf::Vector2f>(ViewResolution));
	view.setRotation(90.f);	// match game's forward vector
	view.setCenter(sf::Vector2f());

	window.setView(view);
}
