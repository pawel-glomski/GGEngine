#include "stdInclude.h"
#include "Client.h"
#include <SFML/Network.hpp>

////////////////////////////////////////////////////////////
/// Send a message to the server, wait for the answer
///
////////////////////////////////////////////////////////////
void runUdpClient(unsigned short port)
{
	// Ask for the server address
	sf::IpAddress server;
	do
	{
		std::cout << "Type the address or name of the server to connect to: ";
		std::cin >> server;
		std::cout << server.toString() << std::endl;
	} while (server == sf::IpAddress::None);

	// Create a socket for communicating with the server
	sf::UdpSocket socket;

	// Send a message to the server
	const char out[] = "Hi, I'm a client";
	if (socket.send(out, sizeof(out), server, port) != sf::Socket::Done)
		return;
	std::cout << "Message sent to the server: \"" << out << "\"" << std::endl;
}

int main()
{
	runUdpClient(55002);
	std::getchar();
	std::getchar();
	return 0;
}