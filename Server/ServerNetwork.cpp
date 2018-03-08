#include "ServerNetwork.h"

void ServerNetwork::run(float_t dt)
{
	lastSentTime += dt;
	if (lastSentTime >= resendInterval)
	{
		lastSentTime = 0;
		sendPackets();
	}
	catchPackets();
}

void ServerNetwork::catchPackets()
{
}

void ServerNetwork::sendPackets()
{
}
