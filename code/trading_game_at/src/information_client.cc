#include "information_client.h"

InformationClient::InformationClient(uint16_t localPort,
									 std::string remoteHost,
									 uint16_t remotePort,
									 IUDPClientHandler& handler) :
	mUDPClient(localPort, remoteHost, remotePort, handler)
{}

void InformationClient::Subscribe()
{
	mUDPClient.Send("TYPE=SUBSCRIPTION_REQUEST");
}
