#include "autotrader.h"
#include "types.h"
#include "pricing_model.h"
#include "parser.h"

#include <boost/optional/optional_io.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <map>
#include <iostream>
#include <fstream>

Autotrader::Autotrader()
{
	LoadInstruments();
	mInformationClient.Subscribe();
}

void Autotrader::Run()
{
	while (true)
	{
		while (mInformationClient.Poll());
		while (mExecutionClient.Poll());
	}
}

void Autotrader::LoadInstruments()
{
	std::ifstream ifs("instruments.lst");
	std::string id;
	double strikePrice;

	while (ifs >> id >> strikePrice)
	{
		mIds.push_back(id);

		const std::experimental::string_view sv{mIds.back()};
		mInstruments[sv] = Instrument{};
	}

	if (mInstruments.empty())
	{
		throw std::runtime_error("error while loading instruments.lst - empty file?");
	}

	std::cout << mInstruments.size() << " instruments loaded" << std::endl;
}

void Autotrader::OnMulticastMessage(std::experimental::string_view msg)
{
	std::size_t pos = 0;
	auto type = ConsumeField<std::experimental::string_view>(msg, "TYPE=", pos);

	if (type == "HEARTBEAT")
	{
		const auto seq = ConsumeField<long>(msg, "SEQ=", pos);
		std::cout << "RX heartbeat, seq " << seq << std::endl;
	}
	else if (type == "THEORETICAL")
	{
		const auto id{ConsumeField<std::experimental::string_view>(msg, "ID=", pos)};
		const Price theoreticalPrice{ConsumeField<double>(msg, "PRICE=", pos)};

		mInstruments[id].mTheoreticalPrice = theoreticalPrice;
	}
	else if (type == "PRICE")
	{
		const auto id{ConsumeField<std::experimental::string_view>(msg, "ID=", pos)};
		const auto action{ConsumeField<std::experimental::string_view>(msg, "ACTION=", pos)};
		const Price price{ConsumeField<double>(msg, "PRICE=", pos)};
		const Volume volume{ConsumeField<double>(msg, "VOLUME=", pos)};

		OnPrice(id, action, price, volume);
	}
	else if (type == "ORDER_ACK")
	{
		std::cout << "RX order ack, " << msg << std::endl;
	}
}

void Autotrader::OnPrice(std::experimental::string_view id,
						 std::experimental::string_view action,
						 Price price,
						 Volume volume)
{
	//std::cout << "RX order, " << id << ": " << action << " " << price.mValue << "@" << volume.mValue << std::endl;

	auto it = mInstruments.find(id);
	if (it == mInstruments.end() || !it->second.mTheoreticalPrice) // we don't know about this - let's ignore it
	{
		return;
	}

	const Price& theoreticalPrice = *it->second.mTheoreticalPrice;

	// happy to buy it if the offer is lower than our theoretical price
	if (action == "SELL" && price.mValue < theoreticalPrice.mValue)
	{
		OrderMessage order{id, Action::Buy, price, volume};
		mExecutionClient.SendOrder(order);
	}
	// happy to sell it if the bid is higher than our theoretical price
	else if (action == "BUY" && price.mValue > theoreticalPrice.mValue)
	{
		OrderMessage order{id, Action::Sell, price, volume};
		mExecutionClient.SendOrder(order);
	}
}




