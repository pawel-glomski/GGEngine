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

	//sf::Packet packet;
	//size_t receivedBytes = 0;
	//sf::IpAddress serverIP = sf::IpAddress("83.20.20.85");
	//unsigned short serverPort = 55002;

	//while (socket.send(package, 128, serverIP, serverPort) != sf::Socket::Status::Done)
	//	std::cout << "Couldn't send data, tries again" << std::endl;
	

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

		//... get data from server and apply it to "world" variable
		//if (socket.receive(packet, serverIP, serverPort))
		//{
		//	ActionCommand* receivedAction = nullptr;
		//	int s;
		//	packet.getData();
		//}
		
		RawInputPack inputPack = inputManager.catchRawInput();
		for (auto input : inputPack.rawKeys)
			std::cout << (uint16_t)input.code << std::endl;
		controllerManager.useController(inputPack);
		// use raw input pack to gui && hud managers

		//... send input data to server
		world.update(deltaTime);

		displayManager.display(world);
		}

	shoutDown();
}

void Client::startUp()
{
	MemoryManager::instance().startUp();
	displayManager.startUp();
	inputManager.startUp(displayManager.getWin());
	controllerManager.startUp();
	world.startUp(controllerManager);
}

void Client::shoutDown()
{
	world.shoutDown();
	controllerManager.shoutDown();
	inputManager.shoutDown();
	displayManager.shoutDown();
	MemoryManager::instance().shoutDown();
}
