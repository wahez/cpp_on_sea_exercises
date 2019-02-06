#pragma once

#include "udp_client.h"

#include <string>
#include <cstdint>

class InformationClient
{
public:
	InformationClient(uint16_t localPort,
					std::string remoteHost,
					uint16_t remotePort,
					IUDPClientHandler& handler);

	void Subscribe();

	bool Poll()
	{
		return mUDPClient.Poll();
	}

private:
	UDPClient mUDPClient;
};
