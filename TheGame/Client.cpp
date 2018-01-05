#include "stdInclude.h"
#include "Client.h"

Client::Client()
{
	//... loading needed data
	settings.loadSettings("data/settings.data");
	
	display.createWindow(settings.graphics);
}

Client& Client::instance()
{
	static Client instance;
	return instance;
}

void Client::play()
{
	while (display.isWinOpen())
	{
		//... get data from server and apply it to "world" variable
		input.handleInput(display.getWin(), settings.getKeyBindings());
		//... send input data to server
		display(world);

	}

	// managers destruction/deallocation in correct order
}
