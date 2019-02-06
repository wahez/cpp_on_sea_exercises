cmake_minimum_required(VERSION 3.5.1)

project(latency_game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g -fno-omit-frame-pointer")

add_subdirectory(src)
//add_subdirectory(tests)
