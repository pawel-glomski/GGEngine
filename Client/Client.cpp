#include "Client.h"

void Client::play()
{
	modules.startUp();

	while(modules.getModule<WindowModule>().getWin().isOpen())
	{
		modules.update(0.016f);
	}

	modules.shoutDown();
}