#include <iostream>
#include "Engine/Game.h"


int main()
try
{
	Game game;
	game.run();

	return 0;	
}
catch(const std::exception & exception)
{
	std::cout << "Catched exception: " << exception.what() << std::endl;
	return 1;
}