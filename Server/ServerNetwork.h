#pragma once
#include <SFML/Network.hpp>
#include <unordered_map>
#include <iostream>

struct Packet
{
	char message[508];
};

inline size_t hash_combine(size_t lhs, size_t rhs)
{
	lhs ^= rhs + 0x9e3779b9 + (lhs << 6) + (lhs >> 2);
	return lhs;
}

struct ClientData
{
	sf::IpAddress ip;
	uint16_t port = 0;

	bool operator==(const ClientData & rhv) const
	{
		return (rhv.ip == ip && port == rhv.port);
	}

	bool operator!=(const ClientData & rhv) const
	{
		return !(rhv == *this);
	}
};

struct ClientDataHasher
{
	size_t operator()(const ClientData & data) const
	{
		return hash_combine(std::hash<std::string>()(data.ip.toString()), std::hash<uint16_t>()(data.port));
	}
};

class ServerNetwork
{
public:

	ServerNetwork();

	void run(float_t dt);

private:

	void catchPackets();

	void sendPackets();


private:

	const float_t resendInterval = 1.f / 1.f;

	float_t lastSentTime = resendInterval;

	sf::UdpSocket socket;

	std::unordered_map<ClientData, std::vector<Packet>, ClientDataHasher> clients;
};

