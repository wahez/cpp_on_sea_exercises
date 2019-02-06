set(sources
	autotrader.h
	autotrader.cc
	execution_client.h
	execution_client.cc
	information_client.h
	information_client.cc
	order_message.h
	parser.h
	pricing_model.h
	pricing_model.cc
	tsc_clock.h
	types.h
	udp_client.h
	udp_client.cc
)

add_library(autotrader_lib ${sources})
target_link_libraries(autotrader_lib papi)

add_executable(autotrader autotrader_main.cc)
target_link_libraries(autotrader autotrader_lib)

find_package(Boost 1.58 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(autotrader ${Boost_LIBRARIES})

