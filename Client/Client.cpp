#include <chrono>
#include <SFML/Network.hpp>
#include "stdInclude.h"
#include "Client.h"

void Client::play()
{
	startUp();

	//sf::UdpSocket socket;
	//socket.setBlocking(false);
	//socket.bind(sf::Socket::AnyPort);

	//char out[128];
	//sf::IpAddress serverIP = sf::IpAddress("83.20.25.19");
	//unsigned short serverPort = 55002;

	//std::cout << "Cliend is sending data, and listening after it sent succesfully" << std::endl;

	//while (socket.send(out, 128, serverIP, serverPort) != sf::Socket::Status::Done)
	//	std::cout << "Couldn't send data, tries again" << std::endl;

	////while (socket.receive(out, 128, sizeof(out), serverIP, serverPort) != sf::Socket::Status::Done)
	////	;
	//std::cout << "Got Message! " << out << std::endl;

	//getchar();

	sf::Clock clock;
	float deltaTime = 0;
	std::chrono::high_resolution_clock::time_point lastTimePoint;
	std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
	auto diff = now - lastTimePoint;

	while (displayManager.getWin()->isOpen())
	{
		now = std::chrono::high_resolution_clock::now();
		diff = now - lastTimePoint;
		lastTimePoint = now;
		deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count() / (float)1000000000.0;

		////... get data from server and apply it to "world" variable
		inputManager.handleInput();
		////... send input data to server
		world.update(deltaTime);

		displayManager.display(world);

	}

	shoutDown();
}

void Client::startUp()
{
	settingsManager.startUp("");
	MemoryManager::instance().startUp();
	displayManager.startUp();
	inputManager.startUp(displayManager.getWin());
	world.startUp(inputManager);
}

void Client::shoutDown()
{
	world.shoutDown();
	inputManager.shoutDown();
	displayManager.shoutDown();
	MemoryManager::instance().shoutDown();
	settingsManager.shoutDown();
}
