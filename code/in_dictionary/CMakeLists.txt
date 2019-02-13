cmake_minimum_required(VERSION 2.8)

project(in_dictionary)

if (MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g -Wall -Wextra -falign-loops=32 -fno-omit-frame-pointer")
endif()

if(DEFINED BENCHMARK_ROOT)
	include_directories(${BENCHMARK_ROOT}/include)
	link_directories(${BENCHMARK_ROOT}/lib)
endif()

add_subdirectory(dictionary_benchmark)

