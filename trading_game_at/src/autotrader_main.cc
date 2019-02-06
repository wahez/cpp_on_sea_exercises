#include "autotrader.h"
#include "tsc_clock.h"

#include <csignal>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <iostream>

extern "C"
{
#include <sys/types.h>
#include <unistd.h>
}

///////////////////////
// NOTE: do NOT edit or move those lines
TSCTimestamp TimestampIn;
///////////////////////

int main()
{
	std::signal(SIGINT, [](int /*sig*/) { std::exit(1); });

	TSCClock::Initialise();

	Autotrader autotrader;
	autotrader.Run();

	return 0;
}
