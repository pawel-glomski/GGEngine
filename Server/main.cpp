#include "stdafx.h"


void runUdpServer(unsigned short port)
{
	sf::UdpSocket socket;

	if (socket.bind(port) != sf::Socket::Done)
		return;
	std::cout << "Server is listening to port " << port << ", waiting for a message... " << std::endl;

	// Wait for a message
	char in[128];
	std::size_t received;
	sf::IpAddress sender;
	unsigned short senderPort;
	if (socket.receive(in, sizeof(in), received, sender, senderPort) != sf::Socket::Done)
		return;
	std::cout << "Message received from client " << sender << " " << senderPort << ": \"" << in << "\"" << std::endl;

	std::cout << sender << " " << std::endl;
}


int main()
{
	sf::UdpSocket socket;
	while (true)
		runUdpServer(55002);

	std::getchar();
	return 0;
}