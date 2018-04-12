#include <iostream>
#include "Client.h"

int main()
try
{
	Client client;
	client.play();

	return 0;
}
catch(const std::exception & exception)
{
	std::cout << exception.what() << std::endl;
	return 1;
}