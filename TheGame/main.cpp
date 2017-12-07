#include "pch.h"
#include "Game.h"

int main()
{
	sf::RenderWindow window({ 1000,600 }, "TheGame");
	sf::Event event;

	while (window.isOpen())
	{

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}
	return 0;
}