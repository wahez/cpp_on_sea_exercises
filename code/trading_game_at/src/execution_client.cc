#include "execution_client.h"
#include "tsc_clock.h"

#include <cstring>
#include <cerrno>
#include <stdexcept>

extern "C"
{
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
}

#include <iostream>

using namespace std::string_literals;

extern TSCTimestamp TimestampIn;

///////////////////////
// NOTE: do NOT edit this line
static const std::string Username = "USERNAME";
///////////////////////

ExecutionClient::ExecutionClient(uint16_t localPort,
								 std::string remoteHost,
								 uint16_t remotePort,
								 IUDPClientHandler& handler) :
	mUDPClient(localPort, remoteHost, remotePort, handler)
{}

void ExecutionClient::SendOrder(OrderMessage order)
{
	//std::cout << "TX order, " << order.mAction << " "
	//		  << order.mVolume.mValue << "@" << order.mPrice.mValue << " "
	//		  << order.mID << std::endl;

	static std::string message;
	message.clear();
	message = "TYPE=ORDER|USERNAME=";
	message += Username;
	message += "|ID=";
	message.append(order.mID.data(), order.mID.size());
	message += "|ACTION=";
	message += order.mAction == Action::Buy ? "BUY" : "SELL";
	message += "|PRICE=";
	message += std::to_string(order.mPrice.mValue);
	message += "|VOLUME=";
	message += std::to_string(order.mVolume.mValue);

	SendSerializedMessage(message);
}

void ExecutionClient::SendSerializedMessage(std::string data)
{
	///////////////////////
	// NOTE: this block can be modified, as long as the timestamp measurement stay
	// the LAST operation before calling sendto()
	{
		const TSCTimestamp timestampOut{TSCClock::now()};
		data += "|LATENCY=" + std::to_string(TSCClock::FromCycles(timestampOut.mValue - TimestampIn.mValue).count());
	}
	//////////////////////

	mUDPClient.Send(data);
}
