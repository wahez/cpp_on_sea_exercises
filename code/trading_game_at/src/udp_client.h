#pragma once

#include "types.h"
#include "../papipp.h"

#include <string>
#include <cstdint>
#include <experimental/string_view>

class IUDPClientHandler
{
public:
	virtual ~IUDPClientHandler() =default;
	virtual void OnMulticastMessage(std::experimental::string_view) =0;
};

class UDPClient
{
public:
	UDPClient(uint16_t localPort, std::string remoteHost, uint16_t remotePort, IUDPClientHandler& handler);

	bool Poll();
	void Send(std::string);

	bool mExec = false;
	papi::event_set<PAPI_L1_DCM, PAPI_L2_DCM, PAPI_L3_TCM, PAPI_RES_STL, PAPI_TOT_CYC, PAPI_TOT_INS> events;

private:
	IUDPClientHandler& mHandler;
	Address mRemote;
	int mSocket;
};
