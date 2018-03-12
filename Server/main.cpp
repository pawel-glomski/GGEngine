#include <iostream>
#include "ServerNetwork.h"

int main()
{
	ServerNetwork server;
	sf::Clock clock;
	while (true)
	{
		server.run(clock.restart().asSeconds());
	}

	return 0;
}