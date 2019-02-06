#pragma once

#include "types.h"

#include <string>
#include <experimental/string_view>

enum struct Action
{
	Buy,
	Sell
};

struct OrderMessage
{
	std::experimental::string_view mID;
	Action mAction;
	Price mPrice;
	Volume mVolume;
};
