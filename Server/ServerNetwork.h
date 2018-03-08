#pragma once
#include <SFML/Network.hpp>
#include "Packets.h"
#include "MathUtilities.h"
#include <string>
#include "Entity.h"

struct ClientData
{
	sf::IpAddress ip;
	uint16_t port = 0;
};

class ServerNetwork
{
public:

	void run(float_t dt);

private:

	void catchPackets();

	void sendPackets();


private:

	const float_t resendInterval = 1000.f / 60.f;

	float_t lastSentTime = resendInterval;


	std::unordered_map<Entity::ID, ClientData> clients;
};

