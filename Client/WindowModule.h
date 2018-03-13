#pragma once
#include <SFML/Graphics.hpp>
#include "Module.h"
#include "MathUtilities.h"

//template<>
//class Settings<WindowModule>
//{
//	enum class WindowSize : uint8_t
//	{
//		S1280x720, S1920x1080,
//		SCount
//	};
//
//
//	WindowSize	windowSize = WindowSize::S1280x720;
//
//	uint32_t	windowType = sf::Style::Close;
//
//
//	static const sf::Vector2u windowSizes[uint8_t(WindowSize::SCount)]; // "resolution" variable can be used as an index in this array
//
//	static const Vec2f ViewResolution;
//
//	static const float_t WorldToWindowRatio;
//};

class WindowModule : public Module<>
{
private:

	using Settings_t = Settings<WindowModule>;

public:

	template<class ...MPtrTypes>
	WindowModule(TuplePlus<MPtrTypes...> & modules) : Base_t(modules) {};


	sf::RenderWindow & getWin();

	const sf::RenderWindow & getWin() const;


private:

	sf::RenderWindow window;

};

