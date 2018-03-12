#include "ServerNetwork.h"

ServerNetwork::ServerNetwork()
{
	socket.setBlocking(false);
	if (socket.bind(54321) != sf::Socket::Done)
		std::cout << "Couldnt bind to port 54321" << std::endl;

}

void ServerNetwork::run(float_t dt)
{
	lastSentTime += dt;

	catchPackets();
	if (lastSentTime >= resendInterval)
	{
		lastSentTime = 0;
		sendPackets();
	}

}

void ServerNetwork::catchPackets()
{
	Packet packet;
	ClientData cData;
	size_t received = 0;
	if (socket.receive(&packet, sizeof(Packet), received, cData.ip, cData.port) == sf::Socket::Done)
	{
		clients[cData];
		if (strlen(packet.message))
		{
			clients[cData].push_back(packet);
			std::cout << " " << packet.message << std::endl;
		}
	}
}

void ServerNetwork::sendPackets()
{
	for (auto & client : clients)
	{
		for (auto & packet : client.second)
			for (auto & otherClient : clients)
				if (client.first != otherClient.first)
					socket.send(&packet, sizeof(Packet), otherClient.first.ip, otherClient.first.port);
		client.second.clear();
	}
}
