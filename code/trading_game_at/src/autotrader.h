#pragma once

#include "execution_client.h"
#include "information_client.h"
#include "udp_client.h"

#include <boost/optional.hpp>

#include <string>
#include <vector>
#include <map>
#include <deque>

struct Instrument
{
	boost::optional<Price> mTheoreticalPrice;
};

class Autotrader : public IUDPClientHandler
{
public:
	Autotrader();
	void Run();

	void OnMulticastMessage(std::experimental::string_view) override;

private:
	void OnPrice(std::experimental::string_view id, std::experimental::string_view action, Price, Volume);

	void SubscribeToPrices();
	void LoadInstruments();

	static constexpr uint16_t InfoServerPort = 7001;
	static constexpr uint16_t ExecServerPort = 8001;

	InformationClient mInformationClient{1235, "127.0.0.1", InfoServerPort, *this};
	ExecutionClient mExecutionClient{1234, "127.0.0.1", ExecServerPort, *this};

	std::deque<std::string> mIds;
	std::map<std::experimental::string_view, Instrument> mInstruments;
};
